#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdio>

#include "AussieLottoException.h"
#include "ResultDownloader.h"
#include "ExceptionHandler.h"

static char curl_error[CURL_ERROR_SIZE];

static const char* failure_message = "Failure to download results.";



int downloadFile(const char *url, const char *destfile, int (*progress_callback)(void *, double, double, double, double), void *ptr)
{

  CURL *curl;
  CURLcode res;
  std::fstream fout;
  std::string newfile(destfile);
  newfile += ".new";
  
  fout.open(newfile.c_str(), std::ios::trunc | std::ios::out | std::ios::binary);
  curl = curl_easy_init();
  curl_global_init(CURL_GLOBAL_ALL);
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_error);
  curl_easy_setopt(curl, CURLOPT_XFERINFODATA, (void*)ptr);
  curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_callback);
#ifndef __linux
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); // Windows may need this.
#endif
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fout);
  try {
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        switch(res)
        {
            case CURLE_COULDNT_CONNECT:
                throw (AussieLottoException(failure_message, curl_error));
                break;
            case CURLE_COULDNT_RESOLVE_HOST:
                throw (AussieLottoException(failure_message, curl_error));
                break;
            case CURLE_READ_ERROR:
                throw (AussieLottoException(failure_message, curl_error));
                break;
            case CURLE_GOT_NOTHING:
                throw (AussieLottoException(failure_message, curl_error));
                break;
            case CURLE_RECV_ERROR:
                throw (AussieLottoException(failure_message, curl_error));
                break;
            default:
                throw(AussieLottoException(failure_message,  curl_error));
                break;
        } //end switch
    } // end if
  } catch (AussieLottoException &e) {
      exceptionHander(e);
      curl_easy_cleanup(curl);
      std::remove(newfile.c_str());
      return -1;
  }

  curl_easy_cleanup(curl);
  fout.close();
  // If successs, delete the old file, and move the new file to the old one.
  std::remove(destfile);
  std::rename(newfile.c_str(), destfile);
  return SUCCESS;

}

size_t write_data(void *ptr, size_t size, size_t nmemb, std::fstream *stream) {
  size_t before = stream->tellp();
  stream->write(reinterpret_cast<char*>(ptr), (size * nmemb));
  size_t after = stream->tellp();
  return (after - before);

}


