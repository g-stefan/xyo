//
// XYO
//
// Copyright (c) 2020-2021 Grigore Stefan <g_stefan@yahoo.com>
// Created by Grigore Stefan <g_stefan@yahoo.com>
//
// MIT License (MIT) <http://opensource.org/licenses/MIT>
//

#include "xyo-version.hpp"

namespace XYO {
	namespace Version {

		static const char *version_ = "4.0.0";
		static const char *build_ = "33";
		static const char *versionWithBuild_ = "4.0.0.33";
		static const char *datetime_ = "2021-03-02 21:25:23";

		const char *version() {
			return version_;
		};
		const char *build() {
			return build_;
		};
		const char *versionWithBuild() {
			return versionWithBuild_;
		};
		const char *datetime() {
			return datetime_;
		};

	};
};
