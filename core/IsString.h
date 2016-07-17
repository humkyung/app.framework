#ifndef	__ISSTRING_H__
#define	__ISSTRING_H__

#include <tchar.h>
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <wchar.h>
#include <vector>

#include <BaseTools.h>
using namespace std;

class IsString
{
public:
	static void TrimLeft(STRING_T& str , const CHAR_T* ch)
	{
		if(str.empty()) return;
		const STRING_T::size_type begin = str.find_first_not_of(ch);
		const STRING_T::size_type size  = str.size();
			
		if(STRING_T::npos == begin)
		{
			str.assign( _T("") );
		}
		else if( begin != 0)
		{
			str.assign(str.substr(begin, size));
		}	
	}
	
	static void TrimRight(STRING_T& str , const CHAR_T* ch)
	{
		if(str.empty()) return;
		
		const STRING_T::size_type end   = str.find_last_not_of(ch) + 1;
		const STRING_T::size_type size  = str.size();
		
		if(0 == end)
		{
			str.assign( _T("") );
		}
		else if(end != size)
		{
			STRING_T a = str.substr(0 , end);
			str.assign(a.c_str());
		}
	}

	template<class T>
	static void TrimWhiteSpace(T& str)
	{
		if(str.empty()) return;
		T::size_type pos = str.find_last_not_of(_T(" \t"));
		if(pos != T::npos) 
		{
			str.erase(pos + 1);
			pos = str.find_first_not_of(_T(" \t"));
			if(pos != T::npos) str.erase(0, pos);
		}
		else str.erase(str.begin(), str.end());
	}

	static void TrimWhiteSpaceA(string& str)
	{
		if(str.empty()) return;
		string::size_type pos = str.find_last_not_of((" \t"));
		if(pos != string::npos) 
		{
			str.erase(pos + 1);
			pos = str.find_first_not_of((" \t"));
			if(pos != string::npos) str.erase(0, pos);
		}
		else str.erase(str.begin(), str.end());
	}

	static void ReplaceOf(STRING_T& str , const STRING_T target, const STRING_T replacement)
	{
		STRING_T::size_type pos = 0, found;

		if (!target.empty())
		{
			STRING_T::size_type target_size = target.size();
			STRING_T::size_type replacement_size = replacement.size();
			while ((found = str.find (target, pos)) != STRING_T::npos)
			{
				str.replace (found , target_size , replacement);
				pos = found + replacement_size;
			}
		}
	}

	static void ToUpper(STRING_T& str)
	{
		transform(str.begin() , str.end() , str.begin() , ::toupper);
	}

	static void ToLower(STRING_T& str)
	{
		transform(str.begin() , str.end() , str.begin() , ::tolower);
	}

	/**
	@brief	return string trimed trailing zero

	@author	humkyung

	@date	2012.02.15
	*/
	static STRING_T TrimedTrailingZero(const double& dValue)
	{
		OSTRINGSTREAM_T oss;
		oss.setf(ios_base::fixed, ios_base::floatfield);
		oss << dValue;

		STRING_T sValue(oss.str());
		STRING_T::size_type at = oss.str().find(_T("."));
		if(STRING_T::npos != at)
		{
			STRING_T sOverDot  = oss.str().substr(0 , at);
			STRING_T sUnderDot = oss.str().substr(at + 1);
			IsString::TrimRight(sUnderDot , _T("0"));

			sValue = sOverDot;
			if(!sUnderDot.empty()) sValue += _T(".");
			sValue += sUnderDot;
		}

		return sValue;
	}
	
	/**
		@brief	

		@author	BHK

		@date	2009.11.09

		@param

		@reutrn
	*/
#if (defined(_UNICODE) || defined(UNICODE))
	static void Format(STRING_T& buffer, const wchar_t* format,...)
	{
		#define MAX_MSG_LENGTH 2048
		CHAR_T sMessage[MAX_MSG_LENGTH] = {'\0',};
		
		buffer = _T("");
		/* put formatted message in sMessage */
		memset(sMessage,0,sizeof(sMessage));
		if(format) 
		{
			va_list args;
			va_start(args, format);
			_vsnwprintf_s(sMessage, MAX_MSG_LENGTH , MAX_MSG_LENGTH - 1 , format, args);
			///_vsnprintf(sMessage, MAX_MSG_LENGTH - 1, sFormat, args);
			sMessage[MAX_MSG_LENGTH-1] = 0;
			va_end(args);

			buffer = sMessage;
		}
	}
#else
	static void Format(STRING_T& str , const CHAR_T* sFormat , ...)
	{
		#define MAX_MSG_LENGTH 2048
		CHAR_T sMessage[MAX_MSG_LENGTH] = {'\0',};
		va_list args;
		
		str = _T("");
		/* put formatted message in sMessage */
		memset(sMessage,0,sizeof(sMessage));
		if(sFormat) 
		{
			va_start(args, sFormat);
			_vsnprintf_s(sMessage, MAX_MSG_LENGTH - 1, MAX_MSG_LENGTH , sFormat, args);
			sMessage[MAX_MSG_LENGTH-1] = 0;
			va_end(args);

			str = sMessage;
		}
	}
#endif

	/**
		@brief	

		@author	BHK

		@date	2009.11.09

		@param

		@reutrn
	*/
	static int CompareNoCase(const STRING_T& lhs , const STRING_T& rhs)
	{
#if (defined(_UNICODE) || defined(UNICODE))
		return _wcsicmp(lhs.c_str() , rhs.c_str());
#else
		return _stricmp(lhs.c_str() , rhs.c_str());
#endif
	}

#if _MSC_VER >= 1310
	/*static std::wstring mbs_to_wcs(const std::string& s)
	{
		std::wstring temp(s.length(),L' ');
		std::copy(s.begin(), s.end(), temp.begin());
		return temp;
	}

	static std::string wcs_to_mbs(const std::wstring& s)
	{
		std::string temp(s.length(), ' ');
		std::copy(s.begin(), s.end(), temp.begin());
		return temp;
	}*/

	static std::wstring mbs_to_wcs(std::string const& str, std::locale const& loc = std::locale())
	{
		typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
		codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
		std::mbstate_t state = std::mbstate_t();
		std::vector<wchar_t> buf(str.size() + 1);
		char const* in_next = str.c_str();
		wchar_t* out_next = &buf[0];
		std::codecvt_base::result r = codecvt.in(state, 
			str.c_str(), str.c_str() + str.size(), in_next, 
			&buf[0], &buf[0] + buf.size(), out_next);
		if (r == std::codecvt_base::error)
			throw std::runtime_error("can't convert string to wstring");   
		return std::wstring(&buf[0]);
	}

	static std::string wcs_to_mbs(std::wstring const& str, std::locale const& loc = std::locale())
	{
		typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
		codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
		std::mbstate_t state = std::mbstate_t();
		std::vector<char> buf((str.size() + 1) * codecvt.max_length());
		wchar_t const* in_next = str.c_str();
		char* out_next = &buf[0];
		std::codecvt_base::result r = codecvt.out(state, 
			str.c_str(), str.c_str() + str.size(), in_next, 
			&buf[0], &buf[0] + buf.size(), out_next);
		if (r == std::codecvt_base::error)
			throw std::runtime_error("can't convert wstring to string");   
		return std::string(&buf[0]);
	}
#endif
};

#endif
