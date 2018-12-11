#!/bin/bash

file=${1}


if [ ! -e "$file"'_RANDOMIZADO_0.1.txt' ]; then
  echo "File: $file not Found!"
else
  mkdir resultadosHelper

  echo "Executando para RANDOMIZADO_0.1" 
    ./trabalhoGrafos-Helper ${file//\/}'_RANDOMIZADO_0.1.txt' >> 'resultadosHelper/'${file//\/}'_RANDOMIZADO_0.1.txt'
fi

if [ ! -e "$file"'_RANDOMIZADO_0.2.txt' ]; then
  echo "File: $file not Found!"
else
  mkdir resultadosHelper

  echo "Executando para RANDOMIZADO_0.2" 
    ./trabalhoGrafos-Helper ${file//\/}'_RANDOMIZADO_0.2.txt' >> 'resultadosHelper/'${file//\/}'_RANDOMIZADO_0.2.txt'
fi

if [ ! -e "$file"'_RANDOMIZADO_0.3.txt' ]; then
  echo "File: $file not Found!"
else
  mkdir resultadosHelper

  echo "Executando para RANDOMIZADO_0.3" 
    ./trabalhoGrafos-Helper ${file//\/}'_RANDOMIZADO_0.3.txt' >> 'resultadosHelper/'${file//\/}'_RANDOMIZADO_0.3.txt'
fi

if [ ! -e "$file"'_REATIVO.txt' ]; then
  echo "File: $file not Found!"
else
  mkdir resultadosHelper

  echo "Executando para REATIVO" 
    ./trabalhoGrafos-Helper ${file//\/}'_REATIVO.txt' >> 'resultadosHelper/'${file//\/}'REATIVO.txt'
fi

