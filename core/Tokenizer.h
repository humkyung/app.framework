//Tokenizer.h

#pragma once

#pragma warning(disable:4786)
#ifdef linux
#else
#include <tchar.h>
#endif
#include <functional>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>

#include <BaseTools.h>
using namespace std;

//For the case the default is a space.
//This is the default predicate for the Tokenize() function.
class CIsSpace : public unary_function<CHAR_T, bool>
{
public:
	bool operator()(CHAR_T c) const;
	STRING_T::const_iterator find(STRING_T::const_iterator& begin , STRING_T::const_iterator& end) const
	{
		STRING_T::const_iterator itr = find_if(begin , end , (*this));
		begin = ((end != itr) ? (itr + 1) : (end));
		return itr;
	}
};

inline bool CIsSpace::operator()(CHAR_T c) const
{
	//isspace<char> returns true if c is a white-space character (0x09-0x0D or 0x20)
#if linux
	return isspace(c) ? true : false;
#else
#if (_MSC_VER >= 1300)
	return isspace(c) ? true : false;
#else
	return isspace<CHAR_T>(c) ? true : false;
#endif
#endif
}

//For the case the separator is a comma
class CIsComma : public unary_function<CHAR_T, bool>
{
public:
	bool operator()(CHAR_T c) const;
	STRING_T::const_iterator find(STRING_T::const_iterator& begin , STRING_T::const_iterator& end) const
	{
		STRING_T::const_iterator itr = find_if(begin , end , (*this));
		begin = ((end != itr) ? (itr + 1) : (end));
		return itr;
	}
};

inline bool CIsComma::operator()(CHAR_T c) const
{
#ifdef	_UNICODE
	return ((_T(',') == c) ? true : false);
#else
	return ((',' == c) ? true : false);
#endif
}

//For the case the separator is a character from a set of characters given in a string
class CIsFromString : public unary_function<CHAR_T, bool>
{
public:
	//Constructor specifying the separators
	CIsFromString(STRING_T const& rostr) : m_ostr(rostr) {}
	bool operator()(CHAR_T c) const;
	STRING_T::const_iterator find(STRING_T::const_iterator& begin , STRING_T::const_iterator& end) const
	{
		STRING_T::const_iterator itr = find_if(begin , end , (*this));
		begin =  ((end != itr) ? (itr + 1) : (end));
		return itr;
	}

private:
	STRING_T m_ostr;
};

inline bool CIsFromString::operator()(CHAR_T c) const
{
	string::size_type iFind = m_ostr.find(c);
	if(iFind != STRING_T::npos)
		return true;
	else
		return false;
}

#ifdef	BOOST_REGEX_USED
#include <boost/regex.hpp>
using namespace boost;

class CIsFromRegExp
{
public:
	CIsFromRegExp(STRING_T const& rostr) : m_regex(rostr){}
	STRING_T::const_iterator find(STRING_T::const_iterator& begin , STRING_T::const_iterator& end) const
	{
		boost::match_results<STRING_T::const_iterator> what;
		if(boost::regex_search(begin , end , what, m_regex))
		{
			begin = what[0].second;
			return what[0].first;
		}
		else
		{
			begin = end;
			return end;
		}
	}
private:
	/*std::string wstring2string(std::wstring wstr) const
	{
		std::string str(wstr.length(),' ');
		copy(wstr.begin(),wstr.end(),str.begin());
		return str;
	}*/

	STRING_T m_ostr;
#ifdef	_UNICODE
	boost::wregex m_regex;
#else
	boost::regex m_regex;
#endif
};

#endif

//String Tokenizer
template <class Pred=CIsSpace>
class CTokenizer
{
public:
	//The predicate should evaluate to true when applied to a separator.
	static void Tokenize(vector<STRING_T>& roResult, STRING_T const& rostr, Pred const& roPred=Pred());
};

//The predicate should evaluate to true when applied to a separator.
template <class Pred>
inline void CTokenizer<Pred>::Tokenize(vector<STRING_T>& roResult, STRING_T const& rostr, Pred const& roPred)
{
	//First clear the results vector
	roResult.clear();

	if(rostr.empty()) return;

	STRING_T::const_iterator it = rostr.begin();
	STRING_T::const_iterator itTokenStart = rostr.begin() , itTokenEnd = rostr.begin();
	while(it != rostr.end())
	{
		//! Find next token
		itTokenStart = it;	//! save current iterator
		itTokenEnd = roPred.find(it , rostr.end());

		//! Append token to result
		if(itTokenStart < itTokenEnd)
			roResult.push_back(STRING_T(itTokenStart, itTokenEnd));
		else if(itTokenStart == itTokenEnd)
			roResult.push_back(STRING_T(_T("")));

		if((rostr.end() == it) && (rostr.end() != itTokenEnd))
		{
			roResult.push_back(STRING_T(_T("")));
		}
	}
}

/**
 * 	author  : humkyung
 * 	purpose : 주어진 문자열을 delimiter로 분리한다.
 * 	date    : 2009-05-12 14:02:04
*/
inline void StringSplit( vector<STRING_T>& results , STRING_T str, const STRING_T& delim)
{
	results.clear();

	string::size_type cutAt = 0;
	while( (cutAt = str.find(delim)) != str.npos )
	{
		if(cutAt > 0)
		{
			results.push_back(str.substr(0,cutAt));
		}
		str = str.substr(cutAt+delim.length());
	}
	if(str.length() > 0)
	{
		results.push_back(str);
	}
}

