// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// A simple unit-test style driver for libfuzzer tests.
// Usage: <fuzzer_test> <file>...

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

//#include "core/fpdfapi/parser/cpdf_document.h"
//#include "core/fpdfapi/parser/cpdf_parser.h"
//#include "core/fpdfapi/parser/cfdf_document.h"

#include <fpdfview.h>
#include <fpdf_text.h>
//#include <unistd.h>
#include <stdio.h>

// Libfuzzer API.
extern "C" {
// User function.
int LLVMFuzzerTestOneInput(const unsigned char* data, size_t size);
// Initialization function.
/*__attribute__((weak))*/ int LLVMFuzzerInitialize(int* argc, char*** argv);
}

std::vector<std::uint8_t> readFile(std::string path) {
  std::ifstream in(path, std::ios::in | std::ios::binary);
  std::vector<std::uint8_t> bin;
  bin.assign(std::istreambuf_iterator<char>(in), {});
  return bin;
}

int main(int argc, char** argv)
{
  FPDF_LIBRARY_CONFIG config;
  config.version = 2;
  config.m_pUserFontPaths = NULL;
  config.m_pIsolate = NULL;
  config.m_v8EmbedderSlot = 0;

  FPDF_InitLibraryWithConfig(&config);

  FPDF_STRING test_doc = "c:/dev/2.pdf";
  FPDF_DOCUMENT doc = FPDF_LoadDocument(test_doc, NULL);
  if (!doc) {
    return 1;
  }
  auto pageCount = FPDF_GetPageCount(doc);
  for (size_t i = 0; i < pageCount; ++i)
  {
    FPDF_PAGE page = FPDF_LoadPage(doc, i);
    FPDF_TEXTPAGE txtPage = FPDFText_LoadPage(page);

    int count = FPDFText_CountChars(txtPage);
    
    std::vector<wchar_t> buf(count);

    int res = FPDFText_GetText(txtPage, 0, 20, (unsigned short*)&buf[0]);
    res;
  }

  FPDF_CloseDocument(doc);
  //if (argc == 1) {
  //  std::cerr << "Usage: " << argv[0] << " <file>..." << std::endl;
  //  exit(1);
  //}

  //auto v = readFile(argv[1]);

  ////CFDF_Document::ParseFile
  //std::unique_ptr<CPDF_Parser> pParser(new CPDF_Parser);
  //std::unique_ptr<CPDF_Document> pDocument(
  //    new CPDF_Document(std::move(pParser)));

  //pDocument->

  //auto doc = CFDF_Document::ParseMemory(&v[0], v.size());
  //if (doc) {
  //  auto root = doc->GetRoot();
  //  root;
  //}
  //if (LLVMFuzzerInitialize)
  //  LLVMFuzzerInitialize(&argc, &argv);

  //for (int i = 1; i < argc; ++i) {
  //  std::cout << argv[i] << std::endl;
  //  auto v = readFile(argv[i]);
  //  LLVMFuzzerTestOneInput((const unsigned char*)v.data(), v.size());
  //}
}
