import pandas as pd
import json

terreno = pd.read_csv("45_45_terreno.csv", header=None)

pista = pd.read_csv("45_45_pista.csv", header=None)

superficies = pd.read_csv("45_45_superficies.csv", header=None)

terreno.to_json("terreno.json")

pista.to_json("pista.json")

superficies.to_json("superficies.json")

with open('pista.json') as json_file:
    pista_json = json.load(json_file)

with open('terreno.json') as json_file:
    terreno_json = json.load(json_file)

with open('superficies.json') as json_file:
    superficies_json = json.load(json_file)

pista = {}

pista["capas"] = {}

pista["capas"]["terreno"] = terreno_json

pista["capas"]["pista"] = pista_json

pista["capas"]["superficies"] = superficies_json

pista["dimensiones"] = {}
pista["dimensiones"]["x"] = 45
pista["dimensiones"]["y"] = 45

pista["tiles"] = {}
# OJO, lo que sigue acá es para el config, no para la pista en si
pista["tiles"]["tilesTierra"] = [i for i in range(90, 116)]
pista["tiles"]["tilesTierra"].extend([j for j in range(117, 131)])
pista["tiles"]["tilesPista"] = [k for k in range(0, 90)]
pista["tiles"]["arena"] = 116
pista["tiles"]["barro"] = 200
pista["tiles"]["aceite"] = 201
pista["tiles"]["vacio"] = -1

with open('pista_prueba.json', 'w') as outfile:
    json.dump(pista, outfile)