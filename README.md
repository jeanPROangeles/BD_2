# **Proyecto 1 Base de datos II**


<img src="https://upload.wikimedia.org/wikipedia/commons/7/7a/UTEC.jpg" width="200">

### **Integrantes**
* Fabian Martin Alvarado Vargas
* Rodrigo Carlos Acosta
* Angello Miguel Zuloaga Loo
*Jean Pier Angeles Barazorda

## **Tabla de contenido**
* [Introducción](#introducción)
* [Técnicas a usar en el proyecto](#técnicas-a-usar)
  * [Extendible Hash](#extendible-hash)
  * [Sequential File](#sequential-file)
* [Resultados](#resultados)
  * [Tiempo de ejecución](#tiempo-de-ejecución)
  * [Gráficos de comparación](#gráficos-de-comparación)
  * [Acessos a memoria secundaria](#accesos-a-memoria-secundaria)
  * [Discusión y análisis de resultados experimentales](#discusión-y-análisis-de-resultados-experimentales)
* [Pruebas y video del proyecto](#pruebas)
# **Introducción**


## **Objetivo del proyecto**
El principal objetivo es desarrollar un SGBD con sus principales funciones para el manejo de datos, utilizando técnicas estudiadas en clase y que sean implementadas de tal forma de que el sistema sea eficiente y amigable para usuario.

## **Dominio de los datos**
Para el dominio de datos...
## **Resultados esperados**
Los resultados esperados son, un SGDB funcional y que mediante las técnicas implementadas sea eficiente, además de poder mostrarlo en una GUI amigable para los usuarios.
# **Técnicas a usar**
- [Extendible Hash](#extendible-hash)
- [Sequential File](#sequential-file)
  

## **Extendible Hash**
<!--- >Explicación de la técnica <--->
Para el almacenamiento de datos se hará uso del funcionamiento de una tabla hash, por lo que dentro de la estructura se hará uso de la función hash proporcionada por el compilador de C ++, lo cual generará cadenas de bits como index para almacenar los registros dentro de los archivos.

<!--- >Funcionamiento de inserción, eliminación y búsqueda <--->
Dentro de las funciones tales como inserción, eliminación y búsqueda, su funcionamiento es el siguiente.

<!--- >Manejo de memoria secundaria <--->
En el archivo "index" se encuentran todos los índices de la estructura, el cual contiene 2^D índices, los cuales apuntan a algún bucket en el archivo de datos. En el archivo de datos, tenemos a los buckets, teniendo en cada uno, un número de registros determinado como máximo, y un número de registros insertados. Cada bucket tiene un ‘D’(Profundidad) local. Cuando se sobrepasa su cantidad máxima de registros del bucket, se divide el índice, se crea un nuevo bucket y se aumenta en uno la profundidad local. Si su profundidad es igual al ‘D’ determinado, entonces se crea un linked bucket, después se consulta al Freelist para verificar si hay buckets eliminados para agregar el linked bucket en dicho espacio, caso contrario se escribe al final del archivo linkeando con el bucket correspondiente.

Además, al eliminar registros, se verifica si se vacía el bucket al eliminar el registro. Además, se verifica si se pueden unir los buckets, en ese caso se hace la unión y se disminuye la profundidad local. Por otro lado, los buckets eliminados se registran con un FreeList, con estrategia LIFO. Por ultimo, la cabecera del FreeList se guarda al inicio del archivo de índices.
 
## **Sequential File**
<!--- >Explicación de la técnica <--->
Para esta técnica, dentro de la organización de los registros, estos se mantendran ordenados por una key dentro del archivo, por lo que en el caso de que no se encuentren el que se insertaron, se linkea cada registro con el siguiente correspondiente. Además, se tiene un archivo auxiliar en el cual se ingresan los registros que no se pueden escribir al final del archivo debido al como está ordenando el archivo.
<!--- >Funcionamiento de inserción, eliminación y búsqueda <--->
Dentro de las funciones tales como inserción, eliminación y búsqueda, su funcionamiento es el siguiente.

<!--- >Manejo de memoria secundaria <--->
Al tener el archivo de registros ordenado. Existe un archivo auxiliar en el que se guardan registros que se deben insertar en el principal pero no tienen espacio, ya que es ordenado y no se realiza la reconstrucción del mismo para evitar que la complejidad de la inserción incremente acorde a la cantidad de registros en el archivo principal. Cada registro tiene un puntero hacia el siguiente registro, el cual puede estar en el principal o auxiliar. Cuando la cantidad de inserciones en el archivo auxiliar, o eliminaciones en total alcanza un límite, se realiza un refactor para reordenar todos los registros en el archivo principal.

Por lo que, la inserción se debe de realizar primero verificando que el archivo principal no tiene algún espacio vacío para insertar el nuevo registro, en el caso de que si disponga se agrega el registro, por el contrario de que no exista espacio libre, se inserta en el archivo auxiliar, y para ambos casos se actualizan los punteros para finalizar la función.

Asimismo, al momento de realizar la eliminación de un registro, lo unico que cambia son los punteros de los registros, liberando espacio para que un nuevo registro sea insertado directamente al archivo principal.


# **Resultados**

## Tiempo de Ejecución
Tiempo medido en segundos

### Inserción de registros

| Técnica | | | | | |
| :-------------------: | --- | --- | --- | --- | --- |
| | 500 registros | 1000 registros | 1500 registros | 2000 registros | 2500 registros |
| Secuencial | 0,038367 | 0,091864 | 0,125376 |0,167607 | 0,21283 | 
| Extendible Hash | 0,037854 | 0,080746 | 0,130043 | 0,190775 | 0,224702 |

### Búsqueda de un registro

| Técnica | | | | | |
| :-------------------: | --- | --- | --- | --- | --- |
| | 500 registros | 1000 registros | 1500 registros | 2000 registros | 2500 registros |
| Secuencial | 0,000194 | 0,000195 | 0,000203 | 0,000216 | 0,000241 | 
| Extendible Hash | 0,000181 | 0,000182 | 0,000182 | 0,000198 | 0,000209 |

### Búsqueda por rango

| Técnica | | | | | |
| :-------------------: | --- | --- | --- | --- | --- |
| | 500 registros | 1000 registros | 1500 registros | 2000 registros | 2500 registros |
| Secuencial | 0,001013 | 0,00171 | 0,001225 | 0,001679 | 0,001810 | 
| Extendible Hash | 0,002442 | 0,003149 | 0,003955 | 0,005072 | 0,005527 |

## Accesos a memoria secundaria
Para obtener los accesos a memoria secundaria dentro de las funciones especificadas, se contará los "reads" y "writes" que haga la función en su tiempo de ejecución.

### Inserción de registros

| Técnica | | | | | |
| :-------------------: | --- | --- | --- | --- | --- |
| | 500 registros | 1000 registros | 1500 registros | 2000 registros | 2500 registros |
| Secuencial | 2491 | 4991 | 7491 | 9991 | 11996 | 
| Extendible Hash | 1184 | 2376 | 4235 | 5735 | 7538 |

### Busqueda de un registro

| Técnica | | | | | |
| :-------------------: | --- | --- | --- | --- | --- |
| | 500 registros | 1000 registros | 1500 registros | 2000 registros | 2500 registros |
| Secuencial | 12 | 13 | 14 | 14 | 14 | 
| Extendible Hash | 1 | 1 | 1 | 1 | 1 |


### Gráficos de comparación

#### Tiempo de ejecución
<img src="/imagenes/insercion_t.JPG" width="600">
<img src="/imagenes/busqueda_t.JPG" width="600">
<img src="/imagenes/busqueda_rt.JPG" width="600">

#### Accesos a memoria secundaria

<img src="/imagenes/accesos_insercion.JPG" width="600">
<img src="/imagenes/acceso_bregistro.JPG" width="600">

## Discusión y análisis de resultados experimentales
Los resultados experimentales muestran que entre ambas técnicas de almacenamiento de datos, existen diferencias significativas en sus tiempos de ejecución acorde a la funcionalidad que se requiera.
Por un lado, tenemos que el “Extendible Hash” tiene una diferencia significativa de tiempo en comparación con el “Sequential File”, esto se debe a que la función hash puede crear “buckets” que no se llenen de datos, cuando se tiene a otros con muchos “linked buckets”, incrementando el tiempo de ejecución mientras más datos se inserten a la vez. Por lo que, el “Sequential File” muestra un mejor rendimiento en este aspecto, porque los archivos son ordenados antes de ser escritos, y no se separan espacios innecesarios al momento de escribir los registros.

Asimismo, cuando es únicamente un solo registro el que se ingresa, la técnica de “Extendible Hash” muestra un mejor rendimiento que el “Sequential File” porque este último, al estar escrito de forma secuencial y ordenada, en el peor de los casos se tiene que ir al final del archivo, que por el contrario dentro de la otra técnica, al generarse la llave, es escrito en los “buckets” creados o por último se inserta uno nuevo, por lo que su complejidad disminuye por su método de acceso. Por lo que, esto mismo se ve reflejado en la búsqueda de un solo registro, porque que tendrían un comportamiento similar en lo que confiere a la lectura del archivo; que para el caso del “Extendible Hash” se va volviendo mucho más eficiente cuando la cantidad de datos incrementa, contrastando con la otra técnica que tiene un comportamiento contrario en cuanto a su tiempo de ejecución.

Por último, encontramos que las búsquedas por rango, son más eficientes dentro del “Sequential File” por su misma organización al momento de escribirse en los archivos, ya que al estar ordenado el acceso es directo. Por el contrario, en la otra técnica se tienen que hacer diversos accesos a distintos “buckets” por lo que ralentiza este tipo de búsqueda.



# **Pruebas**
En el video.https://youtu.be/odKF_Y5CURI (LINK)

#participacion
| lista activididad | responsable|nota|
| :-------------------: | --- | --- | --- | --- | --- | 
| hacer el bucket de los hashing y enlazarlo con los menus y los cvs | rodrigo carlos| |
| crear los menu pokemon y futbol y el record del hashing| jean pier|  | 
| funcion Secuencial |Fabian | |
| funcion Extendible Hash | Angello | |
