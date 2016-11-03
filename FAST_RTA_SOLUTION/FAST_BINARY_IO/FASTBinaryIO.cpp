#include "FASTBinaryIO.h"
#include <iostream>

namespace FASTBinaryIO
{
	class FASTFile
	{
		std::FILE *file;
		IOMODE iomode;
		unsigned long fileLength;
		FASTFile(IOMODE _iomode) : file(nullptr), iomode(_iomode), fileLength(0) { }
		FASTFile(const FASTFile &) { }
		friend FASTFile * Create(IOMODE _iomode);
		friend void ChangeIOMode(FASTFile *_fastFile, IOMODE _iomode);
		friend bool Open(FASTFile *_fastFile, const char *_filePath);
		friend bool Close(FASTFile *_fastFile);
		friend bool ToStart(FASTFile *_fastFile);
		friend bool ToEnd(FASTFile *_fastFile);
		friend bool MoveTo(FASTFile *_fastFile, unsigned long _offset);
		friend bool Move(FASTFile *_fastFile, unsigned long _offset);
		friend bool ReadTo(FASTFile *_fastFile, unsigned long _size, char **_data, unsigned long &_read);
		friend bool ReadAll(FASTFile *_fastFile, char **_data, unsigned long &_read);
		friend bool IsEOF(FASTFile *_fastFile);
		friend bool Write(FASTFile *_fastFile, unsigned long _size, char const *_data, unsigned long &_wrote);
	};

	
	FASTBINARYIO_API FASTFile * Create(IOMODE _iomode)
	{
		return new FASTFile(_iomode);
	}

	FASTBINARYIO_API void Destroy(FASTFile *_fastFile)
	{
		delete _fastFile;
	}

	FASTBINARYIO_API void ChangeIOMode(FASTFile *_fastFile, IOMODE _iomode)
	{
		_fastFile->iomode = _iomode;
	}

	FASTBINARYIO_API bool Open(FASTFile *_fastFile, const char *_filePath)
	{
		char mode[3];
		if (WRITE == _fastFile->iomode)
			strcpy_s(mode, 3, "wb");
		else if (APPEND == _fastFile->iomode)
			strcpy_s(mode, 3, "ab");
		else if (READ == _fastFile->iomode)
			strcpy_s(mode, 3, "rb");
		else
			return false;

		fopen_s(&_fastFile->file, _filePath, mode);
		if (nullptr != _fastFile->file)
		{
			if (READ == _fastFile->iomode)
			{
				fseek(_fastFile->file, NULL, SEEK_END);
				_fastFile->fileLength = ftell(_fastFile->file);
				fseek(_fastFile->file, NULL, SEEK_SET);
			}
			return true;
		}
		return false;
	}
	
	FASTBINARYIO_API bool Close(FASTFile *_fastFile)
	{
		if (fclose(_fastFile->file) == NULL)
			return true;
		return false;
	}

	FASTBINARYIO_API bool ToStart(FASTFile *_fastFile)
	{
		if (fseek(_fastFile->file, NULL, SEEK_SET) == NULL)
			return true;
		return false;
	}
	
	FASTBINARYIO_API bool ToEnd(FASTFile *_fastFile)
	{
		if (fseek(_fastFile->file, NULL, SEEK_END) == NULL)
			return true;
		return false;
	}

	FASTBINARYIO_API bool MoveTo(FASTFile *_fastFile, unsigned long _offset)
	{
		int ret = fseek(_fastFile->file, _offset, SEEK_SET);
		if (READ == _fastFile->iomode)
		{
			fread(nullptr, NULL, NULL, _fastFile->file);
			if (feof(_fastFile->file))
				return false;
		}
		else if (!ret)
			return true;
		return false;
	}

	FASTBINARYIO_API bool Move(FASTFile *_fastFile, unsigned long _offset)
	{
		int ret = fseek(_fastFile->file, _offset, SEEK_CUR);
		if (READ == _fastFile->iomode)
		{
			fread(nullptr, NULL, NULL, _fastFile->file);
			if (feof(_fastFile->file))
				return false;
		}
		else if (!ret)
			return true;
		return false;
	}

	FASTBINARYIO_API bool ReadTo(FASTFile *_fastFile, unsigned long _size, char **_data, unsigned long &_read)
	{
		if (UINT32_MAX == _size)
			return false;
		
		*_data = new char[_size];
		_read = (unsigned long)fread_s(*_data, _size, sizeof(char), _size, _fastFile->file);

		if (_read == _size)
			return true;
		
		int ret = feof(_fastFile->file);

		char *temp = new char[_read];
		memcpy_s(temp, _read, *_data, _read);
		delete[] * _data;
		*_data = temp;
		
		if (ret)
			return true;
		return false;
	}

	FASTBINARYIO_API bool ReadAll(FASTFile *_fastFile, char **_data, unsigned long &_read)
	{
		_read = _fastFile->fileLength;
		*_data = new char[_read];
		_read = (unsigned long)fread_s(*_data, _read, sizeof(char), _read, _fastFile->file);
		
		if (_read == _fastFile->fileLength)
			return true;

		int ret = feof(_fastFile->file);

		char *temp = new char[_read];
		memcpy_s(temp, _read, *_data, _read);
		delete[] * _data;
		*_data = temp;

		if (ret)
			return true;
		return false;
	}

	FASTBINARYIO_API bool IsEOF(FASTFile *_fastFile)
	{
		return feof(_fastFile->file);
	}

	FASTBINARYIO_API bool Write(FASTFile *_fastFile, unsigned long _size, char const *_data, unsigned long &_wrote)
	{
		_wrote = fwrite(_data, sizeof(char), _size, _fastFile->file);
		if (_wrote == _size)
			return true;
		return false;
	}
}
