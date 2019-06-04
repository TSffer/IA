# IA
Trabajos de laboratorio de Inteligencia Artificial

1) Busqueda Ciega y Heurística
  compilar ubuntu: g++ -std=c++11 -O2 main.cpp -o main -lglut -lGLU -lGL
  
2) Damas
  compilar ubuntu: g++ -std=c++11 -O2 main.cpp -o main
  Mover ficha:colocar posicion  DE: vertical - horizontal  -> Hacia: vertical - horizontal
  
3) Algoritmo Genético: Solución de TSP con algoritmos geneticos
  compilar ubuntu: g++ -std=c++11 main.cpp -o main -lglut -lGLU -lGL
  Para cambiar el numero de ciudades entrar a TSP.cpp en las primeras lineas cambiar N_Nodes = numero_deseado, 
  y el numero de iteraciones en main.cpp : tsp->start(numero_deseado);
  
4) Keras/AppResNetv2.py -> red convolucional: Modelo Utilizado ResNet50 de Keras/TensorFlow
  compilar ubuntu: python3 AppResNetv2.py
