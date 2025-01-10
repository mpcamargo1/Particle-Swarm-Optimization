# Implementação de Particle Swarm Optimization (PSO)

Este repositório apresenta uma implementação do algoritmo **Particle Swarm Optimization (PSO)**, uma técnica de otimização inspirada no comportamento coletivo de enxames, como cardumes de peixes e bandos de pássaros. O PSO é amplamente utilizado para resolver problemas de otimização em várias áreas, como aprendizado de máquina, engenharia e economia.

## Principais Funcionalidades
- **Configuração Personalizada**: Possibilidade de ajustar o número de partículas, iteracões, coeficientes de inércia, cognição e social.
- **Visualização do Processo de Otimização**: Opção de plotar o progresso das partículas no espaço de solução (caso implementado).
- **Flexibilidade em Funções de Avaliação**: Suporte para otimizar diferentes funções objetivo.

## O que é Particle Swarm Optimization (PSO)?
O PSO é um algoritmo metaheurístico introduzido por **James Kennedy** e **Russell Eberhart** em 1995. Ele busca soluções ideais iterativamente, simulando o comportamento de um grupo de partículas que se movem no espaço de busca influenciadas pelas melhores experiências individuais e coletivas.

Cada partícula possui:
- **Posição**: Representa uma possível solução.
- **Velocidade**: Controla o movimento da partícula.
- **Histórico Pessoal**: A melhor solução encontrada pela própria partícula.

**Atualização de Velocidade:**
```
v[t+1] = w * v[t] + c1 * r1 * (pbest - x[t]) + c2 * r2 * (gbest - x[t])
```

**Atualização de Posição:**
```
x[t+1] = x[t] + v[t+1]
```

Onde:
- `v[t]`: velocidade atual
- `x[t]`: posição atual
- `w`: fator de inércia
- `c1`, `c2`: coeficientes de cognição e social
- `r1`, `r2`: valores aleatórios entre 0 e 1
- `pbest`: melhor solução da partícula
- `gbest`: melhor solução global

## Aplicações
O PSO pode ser usado em vários contextos, incluindo:
- Otimização de funções matemáticas
- Treinamento de modelos de aprendizado de máquina
- Planejamento e alocação de recursos
- Problemas de engenharia


Compilar com GCC : gcc pso.c mtwister.c -o output
