#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct ResponseBodyChunk {
  char *value;
  size_t size;
};

static size_t WriteBodyCallback(void *contents, size_t size, size_t nmemb, void *chunkp)
{
  size_t realsize = size * nmemb;
  struct ResponseBodyChunk *chunk = (struct ResponseBodyChunk *)chunkp;

  chunk->value = realloc(chunk->value, chunk->size + realsize + 1);
  if(chunk->value == NULL) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(chunk->value[chunk->size]), contents, realsize);
  chunk->size += realsize;
  chunk->value[chunk->size] = 0;

  return realsize;
}

void print_args(int argc, char *argv[]) {
    for(int index=1; index<argc; index++)
    {
        printf("%s\n",argv[index]);
    }
}

char *battle(char *hero, char *villian) {
    CURL *curl;
    CURLcode response;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if(curl) {
        struct ResponseBodyChunk chunk;

        chunk.value = malloc(1);
        chunk.size = 0;   
        
        curl_easy_setopt(curl, CURLOPT_URL, "https://s3.eu-west-2.amazonaws.com/build-circle/characters.json");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteBodyCallback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        response = curl_easy_perform(curl);

        if(response != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(response));
        }
        else{
            printf("%lu bytes retrieved\n", (long)chunk.size);
            printf("%s\n",chunk.value);
        }

        curl_easy_cleanup(curl);
    }else{
        fprintf(stderr, "curl_easy_init() failed: %s\n",
                curl_easy_strerror(response));
    }
    
    return "winner";
}

int main(int argc, char *argv[]) {
    print_args(argc, argv);

    char* winner;

    winner = battle(argv[0], argv[1]);

    printf("The winner is %s\n", winner);
}