//
// XYO
//
// Copyright (c) 2020 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-encoding-utf.hpp"
#include "xyo-encoding-utfstream.hpp"
#include "xyo-system-file.hpp"
#include "xyo-system-shell.hpp"

namespace XYO {
	namespace Encoding {
		namespace Utf {
			using namespace XYO::DataStructures;
			using namespace XYO::System;

			const utf8 utf8StringQuestionMark[] = {'?', 0};
			const utf16 utf16StringQuestionMark[] = {'?', 0};
			const utf32 utf32StringQuestionMark[] = {'?', 0};

			size_t elementUtf32FromUtf8(utf32 *out, const  utf8 *in) {
				size_t in_sz;
				in_sz = Utf8Core::elementSize(*in);
				if (in_sz == 0) {
					return 0;
				};
				if (!Utf8Core::elementIsValid(in)) {
					return 0;
				};
				*out = 0;
				switch (in_sz) {
					case 1:
						*out = (utf32) * in;
						break;
					case 2:
						*out = (utf32) (*in & 0x1F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						break;
					case 3:
						*out = (utf32) (*in & 0x0F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						break;
					case 4:
						*out = (utf32) (*in & 0x07);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						break;
					case 5:
						*out = (utf32) (*in & 0x03);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						break;
					case 6:
						*out = (utf32) (*in & 0x01);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						*out <<= 6;
						++in;
						*out |= (utf32) (*in & 0x3F);
						break;
				};
				if (Utf32Core::elementIsValid(*out)) {
					return 1;
				};
				return 0;
			};

			size_t elementUtf8FromUtf32Size(utf32 in) {
				if (!Utf32Core::elementIsValid(in)) {
					return 0;
				};

				//ISO-10646-UTF-8
				if ((in & 0xFFFFFF80) == 0x00000000) {
					return 1;
				};
				if ((in & 0xFFFFF800) == 0x00000000) {
					return 2;
				};
				if ((in & 0xFFFF0000) == 0x00000000) {
					return 3;
				};
				if ((in & 0xFFE00000) == 0x00000000) { // <-- never here ...
					return 4;
				};
				if ((in & 0xFC000000) == 0x00000000) {
					return 5;
				};
				if ((in & 0x80000000) == 0x00000000) {
					return 6;
				};
				return 0;
			};

			size_t elementUtf8FromUtf32(utf8 *out, utf32 in) {
				size_t sz;
				sz = elementUtf8FromUtf32Size(in);
				if (sz == 0) {
					return 0;
				};
				*out = 0;
				switch (sz) {
					case 1:
						*out = (utf8) in;
						break;
					case 2:
						out += 1;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x1F) | 0xC0);
						break;
					case 3:
						out += 2;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x0F) | 0xE0);
						break;
					case 4:
						out += 3;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x07) | 0xF0);
						break;
					case 5:
						out += 4;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x03) | 0xF8);
						break;
					case 6:
						out += 5;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x3F) | 0x80);
						--out;
						in >>= 6;
						*out = (utf8) ((in & 0x01) | 0xFC);
						break;
				};
				return sz;
			};

			size_t elementUtf16FromUtf32Size(utf32 in) {
				//ISO-10646-UTF-16
				if (!Utf32Core::elementIsValid(in)) {
					return 0;
				};
				if (in <= 0x0000FFFF) {
					return 1;
				};
				return 2;
			};

			size_t elementUtf16FromUtf32(utf16 *out, utf32 in) {
				size_t sz;
				sz = elementUtf16FromUtf32Size(in);
				if (sz == 0) {
					return 0;
				};
				*out = 0;
				switch (sz) {
					case 1:
						*out = (utf16) in;
						break;
					case 2:
						in -= 0x00010000;
						++out;
						*out = (utf16) ((in % 0x0400) + 0xDC00);
						--out;
						*out = (utf16) ((in / 0x0400) + 0xD800);
						break;
				};
				return sz;
			};

			size_t elementUtf32FromUtf16(utf32 *out, const  utf16 *in) {
				size_t sz;
				sz = Utf16Core::elementSize(*in);
				if (sz == 0) {
					return 0;
				};
				if (!Utf16Core::elementIsValid(in)) {
					return false;
				};
				*out = 0;
				switch (sz) {
					case 1:
						*out = (utf32) * in;
						break;
					case 2:
						*out = (*in - 0xD800);
						*out *= 0x400;
						++in;
						*out += (*in - 0xDC00);
						*out += 0x0010000;
						break;
				};
				if (Utf32Core::elementIsValid(*out)) {
					return 1;
				};
				return 0;
			};

			size_t elementUtf8FromUtf16Size(const utf16 *in) {
				if ((*in & 0xFC00) == 0xD800) {
					++in;
					if ((*in & 0xFF80) == 0x0000) {
						return 3;
					};
					if ((*in & 0xF800) == 0x0000) {
						return 4;
					};
					return 5;
				};

				if ((*in & 0xFC00) == 0xDC00) {
					return 0;
				}
				if (*in >= 0xFFFE) {
					return 0;
				};

				if ((*in & 0xFF80) == 0x0000) {
					return 1;
				};
				if ((*in & 0xF800) == 0x0000) {
					return 2;
				};
				return 3;
			};

			String utf8FromUtf16(const utf16 *in, const utf8 *err) {
				String retV;
				utf8 chr[8];
				utf32 tmp;
				size_t sz;

				while(*in) {

					sz = Utf16Core::elementSize(*in);
					if (sz) {
						if (elementUtf32FromUtf16(&tmp, in)) {
							chr[elementUtf8FromUtf32(chr, tmp)] = 0;
							retV += chr;
						} else {
							retV += err;
						};
						in += sz;
						continue;
					};

					retV += err;
					++in;
				};
				return retV;
			};

			String utf8FromUtf32(const utf32 *in, const utf8 *err) {
				String retV;
				utf8 chr[8];
				size_t sz;

				while (*in) {

					sz = Utf32Core::elementSize(*in);
					if (sz) {
						chr[elementUtf8FromUtf32(chr, *in)] = 0;
						retV += chr;
						in += sz;
						continue;
					};

					retV += err;
					++in;
				};
				return retV;
			};

			StringUtf16 utf16FromUtf8(const utf8 *in, const utf16 *err) {
				StringUtf16 retV;
				utf32 tmp;
				utf16 chr[4];
				size_t sz;

				while (*in) {

					sz = Utf8Core::elementSize(*in);
					if (sz) {
						if (elementUtf32FromUtf8(&tmp, in)) {
							chr[elementUtf16FromUtf32(chr, tmp)]=0;
							retV += chr;
						} else {
							retV += err;
						};
						in += sz;
						continue;
					};

					retV += err;
					++in;
				};

				return retV;
			};

			StringUtf16 utf16FromUtf32(const utf32 *in, const utf16 *err) {
				StringUtf16 retV;
				utf16 chr[4];
				size_t sz;

				while(*in) {

					sz = Utf32Core::elementSize(*in);
					if (sz) {
						chr[elementUtf16FromUtf32(chr, *in)]=0;
						retV += chr;
						continue;
					};

					retV += err;
					++in;
				};

				return retV;
			};

			StringUtf32 utf32FromUtf8(const utf8 *in, const utf32 *err) {
				StringUtf32 retV;
				utf32 chr[2];
				size_t sz;

				while (*in) {

					sz = Utf8Core::elementSize(*in);
					if (sz) {
						chr[elementUtf32FromUtf8(chr, in)]=0;
						retV+=chr;
						in += sz;
						continue;
					};

					retV += err;
					++in;
				};

				return retV;
			};

			StringUtf32 utf32FromUtf16(const utf16 *in, const utf32 *err) {
				StringUtf32 retV;
				utf32 chr[2];
				size_t sz;

				while (*in) {
					sz = Utf16Core::elementSize(*in);
					if (sz) {
						chr[elementUtf32FromUtf16(chr, in)]=0;
						retV+=chr;
						in += sz;
						continue;
					};

					retV += err;
					++in;
				};

				return retV;
			};

			size_t utf16FromUtf8Length(const utf8 *in, const utf16 *err) {
				size_t ln = 0;
				utf32 tmp;
				size_t sz;

				while (*in) {
					sz = Utf8Core::elementSize(*in);
					if (sz) {
						if (elementUtf32FromUtf8(&tmp, in)) {
							ln += elementUtf16FromUtf32Size(tmp);
						} else {
							ln += StringUtf16Core::length(err);
						};
						in += sz;
						continue;
					};

					ln += StringUtf16Core::length(err);
					++in;
				};
				return ln;
			};

			size_t utf16FromUtf32Length(const utf32 *in, const utf16 *err) {
				size_t ln = 0;
				size_t sz;

				while (*in) {
					sz = Utf32Core::elementSize(*in);
					if (sz) {
						ln += elementUtf16FromUtf32Size(*in);
						in += sz;
						continue;
					};

					ln += StringUtf16Core::length(err);
					++in;
				};
				return ln;
			};

			size_t utf32FromUtf8Length(const utf8 *in, const utf32 *err) {
				size_t ln = 0;
				size_t lnX;
				size_t sz;
				utf32 chr;

				while(*in) {
					sz = Utf8Core::elementSize(*in);
					if (sz) {
						ln += elementUtf32FromUtf8(&chr, in);
						in += sz;
						continue;
					};

					ln += StringUtf32Core::length(err);
					++in;
				};
				return ln;
			};

			size_t utf32FromUtf16Length(const utf16 *in, const utf32 *err) {
				size_t ln = 0;
				size_t lnX;
				size_t sz;
				utf32 chr;

				while (*in) {
					sz = Utf16Core::elementSize(*in);
					if (sz) {
						ln += elementUtf32FromUtf16(&chr, in);
						in += sz;
						continue;
					};

					ln += StringUtf32Core::length(err);
					++in;
				};
				return ln;
			};

			bool fileGetContentsUtf8(const char *fileName, String &output, int mode) {
				File file;
				Utf8Read utf8Read;

				if (file.openRead(fileName)) {
					if(utf8Read.open(&file, mode)) {
						size_t size;
						size_t strSize;

						file.seekFromEnd(0);
						size = file.seekTell();
						file.seekFromBegin(0);
						strSize = size;
						if(!((mode == UtfStreamMode::None) || (mode == UtfStreamMode::Utf8))) {
							strSize = size * 2;
						};
						TPointer<StringReference> result(TMemory<StringReference>::newMemory());
						result->init(strSize + 1);
						size_t readLn = utf8Read.read(result->value(), strSize);
						(result->value())[readLn] = 0;
						result->setLength(readLn);

						size_t verifyLn = 0;
						switch(mode) {
							case UtfStreamMode::None:
							case UtfStreamMode::Utf8:
								verifyLn = readLn;
								break;
							case UtfStreamMode::Utf16:
								verifyLn = utf16FromUtf8Length(result->value()) * sizeof(utf16);
								break;
							case UtfStreamMode::Utf32:
								verifyLn = utf32FromUtf8Length(result->value()) * sizeof(utf32);
								break;
							default:
								break;
						};
						if(size == verifyLn) {
							utf8Read.close();
							file.close();
							output = result;
							return true;
						};
						result.deleteMemory();
					};
					file.close();
				};
				return false;
			};

			bool filePutContentsUtf8(const char *fileName, const String &value, int mode) {
				File file;
				Utf8Write utf8Write;

				if (file.openWrite(fileName)) {
					if(utf8Write.open(&file, mode)) {
						if (utf8Write.write(value.index(0), value.length()) == value.length()) {
							utf8Write.close();
							file.close();
							return true;
						};
						utf8Write.close();
						file.close();
					};
				};
				return false;
			};


		};
	};
};

