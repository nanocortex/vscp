// vscp_client_tcp.h
//
// tcp/ip client communication classes.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 2 of the License, or (at your option) any later version.
//
// This file is part of the VSCP (https://www.vscp.org)
//
// Copyright:   (C) 2007-2020
// Ake Hedman, Grodans Paradis AB, <akhe@vscp.org>
//
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this file see the file COPYING.  If not, write to
// the Free Software Foundation, 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//

#if !defined(VSCPCLIENTTCP_H__INCLUDED_)
#define VSCPCLIENTTCP_H__INCLUDED_

#include <vscpremotetcpif.h>
#include "vscp_client_base.h"

class vscpClientTcp : public CVscpClient
{

public:

    vscpClientTcp();
    ~vscpClientTcp();

    /*!
        Initialize the tcp client
        @param strHostname Hostname for remote host. Can be prefixed with
            tcp:// or stcp:// (SSL connection)
        @param port Port to connect to on remote host.
        @param strUsername Username used to login on remote host.
        @param strPassword Password used to login on remote host.
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    int init(const std::string &strHostname = "localhost",
                short port = VSCP_DEFAULT_TCP_PORT,
                const std::string &strUsername = "admin",
                const std::string &strPassword = "secret");                  

    /*!
        Connect to remote host
        @param bPoll If true polling is used.
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int connect(void);

    /*!
        Disconnect from remote host
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int disconnect(void);

    /*!
        Check if connected.
        @return true if connected, false otherwise.
    */
    virtual bool isConnected(void);

    /*!
        Send VSCP event to remote host.
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int send(vscpEvent &ev);

    /*!
        Send VSCP event to remote host.
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int send(vscpEventEx &ex);

    /*!
        Receive VSCP event from remote host
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int receive(vscpEvent &ev);

    /*!
        Receive VSCP event ex from remote host
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int receive(vscpEventEx &ex);

    /*!
        Set interface filter
        @param filter VSCP Filter to set.
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int setfilter(vscpEventFilter &filter);

    /*!
        Get number of events waiting to be received on remote
        interface
        @param pcount Pointer to an unsigned integer that get the count of events.
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int getcount(uint16_t *pcount);

    /*!
        Clear the input queue
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int clear(void);

    /*!
        Get version from interface
        @param pmajor Pointer to uint8_t that get major version of interface.
        @param pminor Pointer to uint8_t that get minor version of interface.
        @param prelease Pointer to uint8_t that get release version of interface.
        @param pbuild Pointer to uint8_t that get build version of interface.
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int getversion(uint8_t *pmajor,
                            uint8_t *pminor,
                            uint8_t *prelease,
                            uint8_t *pbuild);

    /*!
        Get interfaces
        @param iflist Get a list of available interfaces
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int getinterfaces(std::deque<std::string> &iflist);

    /*!
        Get capabilities (wcyd) from remote interface
        @return Return VSCP_ERROR_SUCCESS of OK and error code else.
    */
    virtual int getwcyd(uint64_t &wcyd);

   /*!
        Getter/setters for connection timeout
        Time is in milliseconds
    */
    virtual void setConnectionTimeout(uint32_t timeout);
    virtual uint32_t getConnectionTimeout(void);

    /*!
        Getter/setters for response timeout
        Time is in milliseconds
    */
    virtual void setResponeTimeout(uint32_t timeout);
    virtual uint32_t getResponseTimeout(void);

private:

    VscpRemoteTcpIf m_tcp;

    // Connection parameters set by init
    std::string m_strHostname;
    short m_port;
    std::string m_strUsername;
    std::string m_strPassword;
};

#endif
