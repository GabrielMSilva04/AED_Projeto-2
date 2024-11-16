# AED 2023-2024 Trabalho 2 (Topological Sorting with Graphs)

## Grade given
18.8/20

## Contributors
- [GabrielMSilva04](https://github.com/GabrielMSilva04)
- [henriqueft04](https://github.com/henriqueft04)

## Description
This repository contains a C implementation of a Graph Abstract Data Type (ADT) and three algorithms for topological sorting of Directed Acyclic Graphs (DAGs). The project also includes a detailed analysis of algorithm performance and complexity.

## Features

- **Graph ADT Implementation**:
  - `GraphFromFile`: Load graphs from a file.
  - `GraphCopy`: Create copies of graphs.
  - `GraphRemoveEdge`: Remove edges from graphs.
  - `GraphCheckInvariants`: Ensure graph consistency.

- **Topological Sorting Algorithms**:
  1. **Graph Copy Method**: Removes vertices with no incoming edges iteratively.
  2. **Auxiliary Array Method**: Tracks vertex degrees without copying the graph.
  3. **Queue-Based Method**: Uses a queue to manage candidate vertices.

- **Performance Analysis**:
  - Detailed complexity evaluations for all algorithms.
  - Memory usage verified with Valgrind.

## Report

For a detailed explanation of the implementation, complexity analysis, and results, refer to the [project report](Relatório%202ºP%20AED%20114588%20113786.pdf).

