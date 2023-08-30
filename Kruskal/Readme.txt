
DSU - Disjoint Set Union
    La idea básica detrás de DSU es mantener una colección de conjuntos disjuntos,
    donde cada conjunto tiene un representante que se elige de manera única. 
    Cada elemento en un conjunto se asocia con el representante de ese conjunto.
    A medida que se realizan operaciones como unión y búsqueda, 
    los conjuntos pueden combinarse para formar conjuntos más grandes o 
    dividirse en conjuntos más pequeños.


FIND
  La operación de la función find simplemente 
  retorna el representante del conjunto al que pertenece cada nodo.

UNITE
    Usa Find para buscar si ambos nodos cuentan con el mismo representante, si lo hacen no se unen
    si son diferentes se unen. 

KA
    Implementación del algorimo de Kruskal. Aquí se crean los vectores de representante (a usar en find y unite), el de rank, y el MST
    (minimum spanning tree, guaradrá todos los caminos a tomar en el algoritmo). 
    También hace un sort de edges (vector creado en main que contiene los valores de data.txt)
    Después de hacer el sort se va a recorrer edges para llenar el MST, para esto se usa find y unite.

MAIN
    Abre el archivo de texto y lo lee, guarda los vértices y edges en dos variables (n,m)
    Crea el vector de egdes y lo llena de acuerdo a la información del txt
    Indica que el vector de MST será el resultado de el algoritmo de Kruskal en base a edges y a n.
    Es decir que llama a la función KA.
    Imprime el valor de MST. 

nota: ifstream: Streams are used to handle data in a structured
and sequential manner, making it possible to process 
large amounts of data efficiently without loading everything into memory at once. 

Los grafos no dirigidos en Data fueron obtenidos y revisados con la herramienta Visualgo.net

Información e implementación sobre DSU y MST: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/

Lectura de archivo con ifstream https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c 

Uso de <algorithm> para el sort: https://learn.microsoft.com/es-es/cpp/standard-library/algorithm?view=msvc-170 

Union and Find in Kruskal implementation https://courses.cs.duke.edu/spring17/compsci330/Notes/UnionFindAmortize.pdf 