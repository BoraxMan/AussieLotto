#include <curl/curl.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "LottoGame.h"
#include "AussieLottoException.h"
#include "ResultDownloader.h"


static char *curl_error;
const int urlcount = 5;
static const char* failure_message = "Failure to download results.";
static bool dbInitialised = false;

std::string ozLottoResultsURL;
std::string tattsResultsURL;
std::string weekdayTattsResultsURL;
std::string powerballResultsURL;
std::string setforlifeResultsURL;

int populateURL(const std::string &g, const std::string &u)
{
  if (g == tatts_id) {
    tattsResultsURL = u; 
  } else if(g == ozlotto_id) {
    ozLottoResultsURL = u;
  } else if(g == powerball_id) {
    powerballResultsURL = u;
  } else if(g == setforlife_id) {
    setforlifeResultsURL = u;
  } else if(g== weekdaytatts_id) {
    weekdayTattsResultsURL = u;
  }

  return 0;
}

int initResultFileDatabase()
{
  std::string game;
  std::string url;
  if (!dbInitialised) {
    curl_error = new char[CURL_ERROR_SIZE];
    std::ifstream urlsfile;
    urlsfile.open("lottourls", std::ios::in);

    if (!urlsfile.is_open()) {
      return -1;
    }

    for (int x = 0; x < urlcount; ++x) {
      urlsfile >> game;
      urlsfile >> url;
      if (urlsfile.bad()) { return -1;}
      populateURL(game, url);
    }
    urlsfile.close();
    dbInitialised = true;
  }
  return 0;

}

int downloadFile(const char *url, const char *destfile)
{

  CURL *curl;
  CURLcode res;
  std::fstream fout;

  fout.open(destfile, std::ios::trunc | std::ios::out);
  curl_global_init(CURL_GLOBAL_ALL);

  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_error);
  curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fout);
  try {
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      if (res == CURLE_COULDNT_CONNECT) {
	throw (AussieLottoException(failure_message, curl_error));
      } else if (res == CURLE_COULDNT_RESOLVE_HOST) {
	throw (AussieLottoException(failure_message, curl_error));
      } else if (res == CURLE_READ_ERROR) {
	throw (AussieLottoException(failure_message, curl_error));
      } else if (res == CURLE_GOT_NOTHING) {
	throw (AussieLottoException(failure_message, curl_error));
      } else if (res == CURLE_RECV_ERROR) {
	throw (AussieLottoException(failure_message, curl_error));
      } else throw(AussieLottoException(failure_message,  curl_error));
    }
  } catch (AussieLottoException &e) {
    std::cout << e.what() << std::endl;
    std::cout << e.where() << std::endl;
    curl_easy_cleanup(curl);
    return -1;
    }
  curl_easy_cleanup(curl);
  fout.close();
  return SUCCESS;

}
size_t write_data(void *ptr, size_t size, size_t nmemb, std::fstream *stream) {
  size_t before = stream->tellp();
  stream->write(reinterpret_cast<char*>(ptr), (size * nmemb));
  size_t after = stream->tellp();
  return (after - before);

}


int progress_callback(void *clientp,  double dltotal,
		      double dlnow, double ultotal,double ulnow)
{
  std::cout << std::fixed;
  std::cout << dltotal << dlnow << std::endl;
  return 0;

}


