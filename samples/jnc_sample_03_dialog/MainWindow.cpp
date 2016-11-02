//..............................................................................
//
//  This file is part of the Jancy toolkit.
//
//  Jancy is distributed under the MIT license.
//  For details see accompanying license.txt file,
//  the public copy of which is also available at:
//  http://tibbo.com/downloads/archive/jancy/license.txt
//
//..............................................................................

#include "pch.h"
#include "MainWindow.h"
#include "moc_MainWindow.cpp"
#include "MyLib.h"

//..............................................................................

static MainWindow* g_mainWindow = NULL;

MainWindow* getMainWindow ()
{
	return g_mainWindow;
}

//..............................................................................

MainWindow::MainWindow (
	QWidget *parent,
	Qt::WindowFlags flags
	):
	QMainWindow (parent, flags)
{
	Q_ASSERT (!g_mainWindow);
	g_mainWindow = this;
	m_layout = NULL;

	m_body = new QWidget (this);
	m_body->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
	setCentralWidget (m_body);

	QFont font ("Monospace", 9);
	font.setStyleHint (QFont::TypeWriter);

	m_output = new QPlainTextEdit (this);
	m_output->setReadOnly(true);
	m_output->setTextInteractionFlags (Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
	m_output->setLineWrapMode (QPlainTextEdit::NoWrap);
	m_output->setFont (font);

	QDockWidget* dockWidget = new QDockWidget ("Output", this);
	dockWidget->setWidget (m_output);
	addDockWidget (Qt::BottomDockWidgetArea, dockWidget);
}

int MainWindow::output_va (const char* format, va_list va)
{
	QString string;
	string.vsprintf (format, va);
	m_output->moveCursor (QTextCursor::End);
	m_output->insertPlainText (string);
	return string.length ();
}

bool MainWindow::runScript (const QString& fileName)
{
	if (fileName.isEmpty ())
	{
		output ("usage: 02_dialog <script.jnc>\n");
		return false;
	}

	QByteArray fileName_utf8 = fileName.toUtf8 ();

	output ("Parsing...\n");

	m_module->initialize (fileName_utf8.constBegin ());
	m_module->addStaticLib (jnc::StdLib_getLib ());
	m_module->addStaticLib (MyLib_getLib ());

	bool result =
		m_module->parseFile (fileName_utf8.constBegin ()) &&
		m_module->parseImports ();

	if (!result)
	{
		output ("%s\n", jnc::getLastErrorDescription_v ());
		return false;
	}

	output ("Compiling...\n");

	result = m_module->compile ();
	if (!result)
	{
		output ("%s\n", jnc::getLastErrorDescription_v ());
		return false;
	}

	output ("JITting...\n");

	result = m_module->jit ();
	if (!result)
	{
		output ("%s\n", jnc::getLastErrorDescription_v ());
		return false;
	}

	jnc::Namespace* nspace = m_module->getGlobalNamespace ()->getNamespace ();
	jnc::Function* mainFunction = nspace->findFunction ("main");
	if (!mainFunction)
	{
		output ("%s\n", jnc::getLastErrorDescription_v ());
		return false;
	}

	output ("Running...\n");

	result = m_runtime->startup (m_module);
	if (!result)
	{
		output ("%s\n", jnc::getLastErrorDescription_v ());
		return false;
	}

	createLayout ();

	int returnValue;
	result = jnc::callFunction (m_runtime, mainFunction, &returnValue, m_layout);
	if (!result)
	{
		output ("Runtime error: %s\n", jnc::getLastErrorDescription_v ());
		return false;
	}

	output ("Done.\n");
	return true;
}

void MainWindow::createLayout ()
{
	m_runtime->getGcHeap ()->addStaticRoot (&m_layout, m_module->getStdType (jnc::StdType_AbstractClassPtr));

	JNC_BEGIN_CALL_SITE (m_runtime)

	m_layout = jnc::createClass <MyLayout> (m_runtime, QBoxLayout::TopToBottom);
	m_body->setLayout (m_layout->m_qtLayout);

	JNC_END_CALL_SITE ()
}

void MainWindow::closeEvent (QCloseEvent* e)
{
	output ("Shutting down...\n");
	m_runtime->shutdown ();
}

//..............................................................................