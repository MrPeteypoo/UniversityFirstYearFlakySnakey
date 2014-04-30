/*
    Copyright (c) 2013  Steven Mead,
                        School of Computing,
                        University of Teesside,
                        Middlesbrough,
                        UK TS1 3BA
                        email: steven.j.mead@tees.ac.uk

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.
*/
#pragma once

#if !defined    LOG_HPP
#   define      LOG_HPP

#   include <prg/core/types.hpp>
#   include <fstream>
#   include <string>
#   include <sstream>

namespace prg {

/**
    \class Log
    \brief A simple logging class (not threaded).
 */
class Log final {
	public:
		//Forward declarations of classes
		class Message;

        /**
            \return Returns the singleton instance of the log class.
        */
		static Log& instance();

        /** \fn Log& add( const Message& log_text )
            \brief Adds a new Message object.
            \return A reference to the logging object (useful for daisy chaining).
        */
		Log& add( const Message& log_text );

		/** \fn Log& info( const std::string& info_message )
            \brief Adds a simple info message to the log
            \return A reference to the logging object (useful for daisy chaining).
        */
        Log& info( const std::string& info_message );

        /** \fn Log& warn( const std::string& warning_message )
            \brief Adds a simple warning message to the log
            \return A reference to the logging object (useful for daisy chaining).
        */
        Log& warn( const std::string& warning_message );

        /** \fn Log& error( const std::string& error_message )
            \brief Adds a simple error message to the log
            \return A reference to the logging object (useful for daisy chaining).
        */
        Log& error( const std::string& error_message );

        /** \fn Log& toStdout( bool to_stdout = false )
            \brief Changes whether messages are also output to standard output STDOUT (errors to STDERR).
            \return A reference to the logging object (useful for daisy chaining).
        */
        Log& toStdout( bool to_stdout = false ) { to_stdout_ = to_stdout; return *this; }

	private:
        //Hidden Constructor/Destructor/Assignment operator
        Log();
        ~Log();
        Log( const Log& )                   = delete;
        Log( Log&& )                        = delete;
        Log& operator=( const Log& copy )   = delete;
        Log& operator=( Log&& copy )        = delete;

		//Data members
		std::ofstream				file_;
		bool                        to_stdout_ = false;
};

/**
    \brief The base class of all log message types.
 */
class Log::Message final : public std::stringstream {
	public:
        enum ELogType : unsigned short {
            LT_Info     = 1,
            LT_Warning  = 2,
            LT_Error    = 3
        };

        /**
            \brief Constructor.
            \param s The string to output the the log file.
        */
		Message( ELogType eType = LT_Info ) : e_message_type_( eType )
		{
		    switch( eType ) {
		        case LT_Info:
                    *this << "I: "; break;
                case LT_Warning:
                    *this << "W: "; break;
                case LT_Error:
                    *this << "E: "; break;
		    }
		}

		Message( const Message& copy )
		{
            *this << copy.str();
		}

		/**
            \brief Destructor.
        */
		~Message() {}

		Message& operator=( const Message& copy )
		{
		    if( this != &copy ) {
                *this << copy.str();
		    }
		    return *this;
		}

        ELogType
        getMessageType() const
        {
            return e_message_type_;
        }

	private:
		ELogType        e_message_type_;
};


extern Log& logger;

}//namespace prg

#endif // LOG_HPP
