#!/bin/bash

gcc game.c menu.c main.c -o velha -lSDL
echo 'Programa compliado...'
echo 'Digite "./velha" para executar o programa'
