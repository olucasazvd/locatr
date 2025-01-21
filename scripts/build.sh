#!/bin/bash
gcc src/main.c src/model.c lib/cJSON.c -o bin/locatr -lcurl
