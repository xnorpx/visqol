/*
 * Copyright 2019 Google LLC, Andrew Hines
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VISQOL_INCLUDE_FILEPATH_H
#define VISQOL_INCLUDE_FILEPATH_H

#include <fstream>
#include <string>

#if defined(_MSVC_LANG)

#endif

#ifndef NO_BOOST
#include "boost/filesystem.hpp"
namespace filesystem = ::boost::filesystem;
#else 
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#include <filesystem>
namespace filesystem = ::std::filesystem;
#else
#error You need boost::filesystem or C++17 with filesystem support
#endif
#endif

namespace Visqol {
class FilePath {
 public:
  FilePath() {}

  FilePath(const FilePath &other) { path_ = other.path_; }

  FilePath(const std::string &path) {
    path_ = ::filesystem::path(path).string();
  }

  const std::string Path() const { return path_; }

  bool Exists() const { return ::filesystem::exists(path_); }

  static std::string currentWorkingDir() {
    return ::filesystem::current_path().string();
  }

 private:
  std::string path_;
};

struct ReferenceDegradedPathPair {
  FilePath reference;
  FilePath degraded;
};
}  // namespace Visqol

#endif  // VISQOL_INCLUDE_FILEPATH_H
