#pragma once

#define FASTBINARYIO_EXPORTS
#ifdef FASTBINARYIO_EXPORTS
#define FASTBINARYIO_API __declspec(dllexport)
#else
#define FASTBINARYOP_API __declspec(dllimport)
#endif

namespace FASTBinaryIO
{
	class FASTFile;
	enum IOMODE
		{
			WRITE,
			APPEND,
			READ,
			NUMIOS
		};
	
	FASTBINARYIO_API FASTFile * Create(IOMODE _iomode);
	FASTBINARYIO_API void Destroy(FASTFile *_fastFile);
	FASTBINARYIO_API bool Open(FASTFile *_fastFile, const char *_filePath);
	FASTBINARYIO_API bool Close(FASTFile *_fastFile);
	FASTBINARYIO_API bool ToStart(FASTFile *_fastFile);
	FASTBINARYIO_API bool ToEnd(FASTFile *_fastFile);
	FASTBINARYIO_API bool MoveTo(FASTFile *_fastFile, unsigned long _offset);
	FASTBINARYIO_API bool Move(FASTFile *_fastFile, unsigned long _offset);
	FASTBINARYIO_API bool ReadTo(FASTFile *_fastFile, unsigned long _size, void **_data, unsigned long &_read);
	FASTBINARYIO_API bool ReadAll(FASTFile *_fastFile, void **_data, unsigned long &_read);
	FASTBINARYIO_API bool IsEOF(FASTFile *_fastFile);
	FASTBINARYIO_API bool Write(FASTFile *_fastFile, unsigned long _size, char const *_data, unsigned long &_wrote);
}
