#!/bin/bash
gcc -o bin/locatr src/main.c src/model.c src/request.c src/asciiart.c lib/cJSON.c -Iinclude -lcurl
