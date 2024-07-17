# Explicação: [Problema 01](https://atcoder.jp/contests/abc143/tasks/abc143_e)

Na questão precisamos determinar menores caminhos para ir de uma cidade a outra considerando que o carro não pode ficar sem combustível e que cada unidade de distância de uma cidade a outra equivale a uma unidade de combustível. Vale lembrar que o automóvel só consegue abastecer quando está em alguma das cidades, representadas pelos vértices do nosso grafo.

Caso não aja caminhos, o programa deverá retornar -1, e caso exista, deverá retornar quantas vezes o carro deverá abastecer. A ideia é priorizar o mínimo de vezes que o carro abastecerá para percorrer da cidade inicial até o destino final.
