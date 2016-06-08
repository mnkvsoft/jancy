namespace io {

//.............................................................................

enum SerialFlowControl
{
	None = 0,
	RtsCts,
	XOnXOff,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum SerialStopBits
{
	_1  = 0,
	_15 = 1,
	_2  = 2
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum SerialParity
{
	None = 0,
	Odd,
	Even,
	Mark,
	Space,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum SerialStatusLines
{
	Cts,
	Dsr,
	Ring,
	Dcd,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum SerialEvent
{
	IncomingData,
	IoError,
	TransmitBufferReady,
	StatusLineChanged,
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct SerialEventParams
{
	SerialEvent m_eventKind;
	uint_t m_syncId;
	SerialStatusLines m_lines;
	SerialStatusLines m_mask;
	std.Error* m_error;
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class Serial
{
public:
	uint_t autoget property m_baudRate;
	SerialFlowControl autoget property m_flowControl;
	uint_t autoget property m_dataBits; // typically 5..8
	SerialStopBits autoget property m_stopBits;
	SerialParity autoget property m_parity;

	SerialStatusLines const property m_statusLines;

	bool autoget property m_dtr;
	bool autoget property m_rts;

	bool readonly m_isOpen;
	uint_t m_syncId;*/

	void construct ();
	void destruct ();

	bool open (char const* name);
	void close ();

	size_t read (
		void* p,
		size_t size
		);

	size_t write (
		void const* p,
		size_t Size
		);

	event m_onSerialEvent (SerialEventParams const* params);
};

//.............................................................................

// serial port enumeration

struct SerialPortDesc
{
public:
	SerialPortDesc const* m_next;
	char const* m_deviceName;
	char const* m_description;
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

SerialPortDesc const* createSerialPortDescList (size_t* count = null);

//.............................................................................

} // namespace io
