

#include "func.h"
#ifdef __cplusplus
extern "C" {  // only need to export C interface if
			  // used by C++ source code
#endif

	__declspec(dllexport) bool __stdcall tccheck( const wchar_t* text_, const  wchar_t* format_string_, const wchar_t* delimiter, signed int* initial_value,
		signed int* elapsed, signed int* start, signed long allow_equal_)
	{		
		bool isvalid = true;		
		BOOL allow_equal = TRUE;
		if (allow_equal_ < 0) { allow_equal = FALSE; }
		//else { allow_equal = TRUE; }
		std::wstring text;
		text.append(text_);
		std::wstring format_string;
		format_string.append(format_string_);
		size_t  n = 0;
		//allow_equal = static_cast<bool>(allow_equal_);		


		while (isvalid)
		{
			isvalid = checktcord(text, format_string, *delimiter, *initial_value, *elapsed, *start, allow_equal);
			initial_value = elapsed;
			if (!(*start < text.length())) { break; }

		}
		return isvalid;

		
	}

	__declspec(dllexport) bool __stdcall is_tcless_(const wchar_t* text, const wchar_t* format_string, const wchar_t* delimiter, signed int* comp_value, signed int* elapsed)
	{
		std::wstring text_,format_string_;
		text_.append(text);
		format_string_.append(format_string);
		bool isless = false;
		isless = is_tcless(text_, format_string_, *delimiter, *comp_value, *elapsed);
		return isless;

	}

	__declspec(dllexport) bool __stdcall add_(const wchar_t* text, const wchar_t* format_string, const wchar_t* delimiter, wchar_t* new_tc, signed int* add, signed int* parsed, signed int* elapsed, signed int* pos)
	{
		std::wstring text_, format_string_,new_tc_,path;
		//path = L"C:\\users\\avduryagin\\file_.txt";
		text_.append(text);
		if (!text_.length() > 0) { return true; }
		format_string_.append(format_string);
		bool success = false,save=true;
		std::list<wformat> form;
		form = parse_format(format_string_, *delimiter);
		success = add_seconds(text_, form, *add, *parsed, *elapsed, *pos);
		if (success)
		{
			new_tc_ = to_tc(*elapsed, form);
			
			for (size_t i = 0; i<new_tc_.length(); i++)
			{
				new_tc[i] = new_tc_.c_str()[i];
			}

		}
		/*else
		{
			std::wofstream fout(path);
			std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
			fout.imbue(loc);
			//fout << text_ << std::endl;
			fout << format_string_ << std::endl;
			fout << *delimiter << std::endl;
			fout << *new_tc << std::endl;
			fout << *add << std::endl;
			fout << *parsed << std::endl;
			fout << *elapsed << std::endl;
			fout << *pos << std::endl;
			fout.close();
		}*/
		return success;
	};

	__declspec(dllexport) signed int __stdcall add_and_replace(const wchar_t* text, const wchar_t* format_string, const wchar_t* delimiter, wchar_t* replaced, signed int* add)
	{
		signed int count = 0,parsed=0,elapsed=0,position=0;
		size_t length = 0;
		std::wstring text_, format_string_, new_tc_, path;
		
		//path = L"C:\\users\\avduryagin\\file_.txt";
		text_.append(text);
		if (!text_.length() > 0) { return count; }
		length = text_.length();
		wchar_t* ntext_ = new wchar_t[length];
		size_t i = 0;
		while (i < length)
		{
			ntext_[i] = text_.at(i);
			++i;
		}
		format_string_.append(format_string);
		bool success = true;
		size_t current_pos = 0;
		std::list<wformat> form;
		form = parse_format(format_string_, *delimiter);
		while (success) 
		{
			success = add_seconds(text_, form, *add, parsed, elapsed, position);
			if (success)
			{
				new_tc_ = to_tc(elapsed, form);
				current_pos = position - new_tc_.length();
				if (!(current_pos <0)) 
				{
					for (size_t j = 0; j < new_tc_.length(); j++)
					{
						ntext_[current_pos + j] = new_tc_.c_str()[j];
					}
					++count;
				}
			}
			
		}
		i = 0;
		while (i < length)
		{
			replaced[i] = ntext_[i];
			++i;
		}
		delete[] ntext_;
		return count;
	};

__declspec(dllexport) bool __stdcall isvalidfs(const wchar_t& format_string,const wchar_t& delimiter)
{
	std::wstring fs;	
	fs.append(&format_string);
	bool isvalid;
	isvalid= fisvalid(fs, delimiter);
	return isvalid;
};

__declspec(dllexport) bool __stdcall chkfs(const wchar_t* format_string, const wchar_t* delimiter,signed int* nsymb)
{
	std::wstring fs;
	fs.append(format_string);
	bool isvalid;
	isvalid = fisvalid(fs, *delimiter,*nsymb);
	return isvalid;
};
 signed int __stdcall nincl(wchar_t& text_, wchar_t& delimiter)
{
	size_t i,j,count = 0;	
	i = 0;
	j = 0;
	std::wstring text;
	text.append(&text_);
	while(j<text.length())
	{
		j = text.find(delimiter, i);
		if (j < text.length()) { count++; }
		i = j+1;
	}
	
	return count;

}


 __declspec(dllexport) signed int __stdcall nsubstr(wchar_t& str, wchar_t& substr)
{
	std::wstring s;
	s.append(&str);

	return nsubstr_(s, substr);

};

 __declspec(dllexport) bool __stdcall save_to_file(const wchar_t* text, const wchar_t* path)
 {
	 bool success = true;
	 std::wstring text_;
	 std::wstring path_;
	 text_.append(text);
	 path_.append(path);
	 success = save_to_file(text_, path_);
	 return success;

 
 }

#ifdef __cplusplus
}
#endif