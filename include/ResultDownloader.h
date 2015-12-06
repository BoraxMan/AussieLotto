#ifndef RESULTDOWNLOADER_H
#define RESULTDOWNLOADER_H

enum resultRetreivalErrors {
  SUCCESS,
  NO_HOST,
  READ_ERROR,
  OTHER_ERROR,
  NO_CONNECT
};


int initResultFileDatabase();
int populateURL(const std::string &g, const std::string &u);


int downloadFile(const char *url, const char *destfile);
size_t write_data(void *ptr, size_t size, size_t nmemb, std::fstream *stream);
int progress_callback(void *clientp,
  double dltotal,
  double dlnow,
  double ultotal,
  double ulnow);

#endif
