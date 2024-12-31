import os
import re

def capitalizar_palabras(nombre):
    # Divide el nombre en partes usando "_"
    partes = nombre.split("_")
    # Capitaliza la primera letra de cada parte (si no es un número)
    partes_capitalizadas = [parte.capitalize() if not parte.isdigit() else parte for parte in partes]
    # Une las partes sin espacios ni guiones bajos
    return "".join(partes_capitalizadas)

def renombrar_archivos(carpeta):
    # Recorre todos los archivos en la carpeta
    for nombre_archivo in os.listdir(carpeta):
        # Verifica si el archivo termina en .png
        if nombre_archivo.endswith(".png"):
            # Separa el nombre y la extensión
            nombre, extension = os.path.splitext(nombre_archivo)
            
            # Capitaliza las palabras y elimina los guiones bajos
            nuevo_nombre = capitalizar_palabras(nombre)
            
            # Añade la letra "n" al principio del nombre
            nuevo_nombre_completo = "n" + nuevo_nombre + extension
            
            # Si el nombre cambió, renombra el archivo
            if nuevo_nombre_completo != nombre_archivo:
                ruta_vieja = os.path.join(carpeta, nombre_archivo)
                ruta_nueva = os.path.join(carpeta, nuevo_nombre_completo)
                os.rename(ruta_vieja, ruta_nueva)
                print(f'Renombrado: {nombre_archivo} -> {nuevo_nombre_completo}')

if __name__ == "__main__":
    # Especifica la carpeta actual (donde se ejecuta el script)
    carpeta_actual = os.getcwd()
    
    # Llama a la función para cambiar los nombres
    renombrar_archivos(carpeta_actual)