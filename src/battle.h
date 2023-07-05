#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./jsmn.h"
#include <curl/curl.h>

struct Character {
    char *name;
    float score;
    enum {HERO,VILLIAN} type; 
    char *weakness; 
};

struct ResponseBodyChunk {
  char *value;
  size_t size;
};

static int jsoneq(const char *json, jsmntok_t *tok, char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

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

float get_character_score(int parse_result, jsmntok_t *json_tokens, char *json_string, char *character_name) {

  /* Loop over all keys of the root object */
  for (int index = 1; index < parse_result; index++) {
    // if (parse_result < 1 || (json_tokens[i].type != JSMN_OBJECT && json_tokens[i].type != JSMN_ARRAY)) {
    //     printf("key: %.*s\n", json_tokens[i].end - json_tokens[i].start,
    //     json_string + json_tokens[i].start);
    // }
    if (jsoneq(json_string, &json_tokens[index], "weakness") == 0) {
      index++;
    }
    else if (jsoneq(json_string, &json_tokens[index], character_name) == 0) {
      /* We may use strndup() to fetch string value */
      char* score;
      score = strndup(json_string + json_tokens[index + 2].start, json_tokens[index + 2].end - json_tokens[index + 2].start);
      index++;
      return atof(score);
    }
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
        else {
            jsmn_parser json_parser;
            int token_count = 512;
            int parse_result;
            jsmntok_t json_tokens[token_count];
            jsmn_init(&json_parser);
            parse_result = jsmn_parse(&json_parser, chunk.value, chunk.size, json_tokens, token_count); // "s" is the char array holding the json content

            if (parse_result < 0) {
                printf("Failed to parse JSON: %d\n", parse_result);
                return "";
            }

            float heroScore;
            float villianScore;

            heroScore = get_character_score(parse_result, json_tokens, chunk.value, hero);
            villianScore = get_character_score(parse_result, json_tokens, chunk.value, villian);
            
            if(villianScore < heroScore){
                return hero;
            }
            else{
                return villian;
            }
        }

        curl_easy_cleanup(curl);
    }else{
        fprintf(stderr, "curl_easy_init() failed: %s\n",
                curl_easy_strerror(response));
    }

    return "";
}