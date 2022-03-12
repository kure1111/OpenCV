Se compila los diferentes programas para el procesamiento Digital de imagenes con OpenCV y C++ utilizados para
el reconocimiento de patrones en imagenes, filtros, Segmentacion y operaciones diversas en imagenes.

Ambiente linux
Para compilar y ejecutarlo haber instalado previamiente la libreria OpenCV

por ejemplo:

compilar desde terminal:

g++ model_2.cpp -o model2 $(pkg-config --cflags --libs opencv)

ejecutar ejemplo:

./model2 I47.png

donde I47.png es ua imagen que recibe como parametro