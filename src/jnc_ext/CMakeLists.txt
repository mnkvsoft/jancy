#...............................................................................
#
#  This file is part of the Jancy toolkit.
#
#  Jancy is distributed under the MIT license.
#  For details see accompanying license.txt file,
#  the public copy of which is also available at:
#  http://tibbo.com/downloads/archive/jancy/license.txt
#
#...............................................................................

set (CMAKE_INSTALL_RPATH)
set (CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

add_subdirectory (jnc_rtl)
add_subdirectory (jnc_std)
add_subdirectory (jnc_sys)
add_subdirectory (jnc_io_cmn)

option (
	BUILD_JNC_IO_BASE
	"Build jancy base IO (sockets, serial ports, files) extension library "
	ON
	)

if (BUILD_JNC_IO_BASE)
	add_subdirectory (jnc_io_base)
endif ()

if (LIBSSH2_FOUND)
	option (
		BUILD_JNC_IO_SSH
		"Build jancy SSH IO extension library"
		ON
		)

	if (BUILD_JNC_IO_SSH)
		add_subdirectory (jnc_io_ssh)
	endif ()
endif ()

if (PCAP_FOUND)
	option (
		BUILD_JNC_IO_PCAP
		"Build jancy PCAP IO extension library"
		ON
		)

	if (BUILD_JNC_IO_PCAP)
		add_subdirectory (jnc_io_pcap)
	endif ()
endif ()

if (LIBUSB_FOUND)
	option (
		BUILD_JNC_IO_USB
		"Build jancy USB IO extension library"
		ON
		)

	if (BUILD_JNC_IO_USB)
		add_subdirectory (jnc_io_usb)
	endif ()
endif ()

if (DEVMON_FOUND)
	option (
		BUILD_JNC_IO_DEVMON
		"Build jancy IO device monitoring extension library"
		ON
		)

	if (BUILD_JNC_IO_DEVMON)
		add_subdirectory (jnc_io_devmon)
	endif ()
endif ()

#...............................................................................
