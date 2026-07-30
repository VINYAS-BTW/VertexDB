# MYDB

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg">
  <img src="https://img.shields.io/badge/Build-CMake-green.svg">
  <img src="https://img.shields.io/badge/License-MIT-orange.svg">
  <img src="https://img.shields.io/badge/Status-In%20Development-yellow.svg">
</p>

---

## Overview

**MYDB** is a modern relational database management system (RDBMS) written completely from scratch in **C++17**.

The goal of this project is not simply to build a database, but to understand how industrial database engines like **PostgreSQL**, **MySQL (InnoDB)**, **SQLite**, and **BusTub** work internally.

Instead of using existing database libraries, every major component is implemented from the ground up, including:

- Storage Engine
- Buffer Pool Manager
- Disk Manager
- B+ Tree Index
- Write-Ahead Logging (WAL)
- Transaction Management
- Concurrency Control
- SQL Parser
- Query Executor

This project serves both as a learning journey and as a production-inspired database implementation.

---

# Objectives

The primary goals of this project are:

- Learn database internals from first principles.
- Implement core storage engine components.
- Understand how pages are stored on disk.
- Build an efficient buffer manager.
- Implement indexing using B+ Trees.
- Add ACID-compliant transactions.
- Implement Write-Ahead Logging.
- Design a SQL parser and execution engine.
- Explore concurrency control and recovery algorithms.

---

# Features (Planned)

## Storage Engine

- Fixed-size pages (4096 bytes)
- Page abstraction
- Disk manager
- Buffer Pool
- LRU Page Replacement
- Free Page Management

---

## Indexing

- B+ Tree
- Range Scan
- Point Lookup
- Node Split
- Node Merge
- Overflow Handling

---

## Transaction Manager

- Begin Transaction
- Commit
- Abort
- Isolation Support
- MVCC (Future)

---

## Concurrency

- Shared Locks
- Exclusive Locks
- Two Phase Locking
- Deadlock Detection (Future)

---

## Recovery

- Write Ahead Logging
- REDO
- UNDO
- Crash Recovery

---

## SQL Engine

Support for

```sql
CREATE TABLE

INSERT

UPDATE

DELETE

SELECT

WHERE

ORDER BY

LIMIT
```

Future support

```sql
JOIN

GROUP BY

HAVING

INDEX SCAN

QUERY OPTIMIZER
```

---

# Current Project Structure

```
MYDB
│
├── src
│   │
│   ├── storage
│   │   ├── page.h
│   │   ├── page.cpp
│   │   ├── disk_manager.h
│   │   ├── disk_manager.cpp
│   │   ├── buffer_pool.h
│   │   ├── buffer_pool.cpp
│   │
│   ├── index
│   │   ├── btree.h
│   │   └── btree.cpp
│   │
│   ├── wal
│   │   ├── log_record.h
│   │   ├── log_manager.h
│   │   └── log_manager.cpp
│   │
│   ├── txn
│   │   ├── transaction.h
│   │   ├── lock_manager.h
│   │   └── txn_manager.cpp
│   │
│   ├── parser
│   │   ├── lexer.h
│   │   ├── parser.h
│   │   ├── parser.cpp
│   │   └── ast.h
│   │
│   ├── executor
│   │   ├── executor.h
│   │   └── executor.cpp
│   │
│   └── main.cpp
│
├── tests
│
├── third_party
│
├── CMakeLists.txt
│
├── Dockerfile
│
└── README.md
```

---

# Architecture

```
                 SQL Query
                     │
                     ▼
               SQL Parser
                     │
                     ▼
             Abstract Syntax Tree
                     │
                     ▼
              Query Executor
                     │
          ┌──────────┴──────────┐
          │                     │
          ▼                     ▼
      Transaction         B+ Tree Index
          │                     │
          └──────────┬──────────┘
                     ▼
             Buffer Pool Manager
                     │
             LRU Page Replacer
                     │
                     ▼
               Disk Manager
                     │
                     ▼
                Database File
```

---

# Storage Layer

The storage layer is the foundation of the database.

Components include:

### Page

Represents one fixed-size database page.

Stores

- Page ID
- Dirty Bit
- Pin Count
- LSN
- Raw Page Data

---

### Disk Manager

Responsible for

- Reading Pages
- Writing Pages
- Allocating Pages
- Persistent Storage

---

### Buffer Pool

Acts as an in-memory cache for disk pages.

Responsibilities

- Fetch Page
- New Page
- Delete Page
- Flush Page
- Pin / Unpin Pages

---

### LRU Replacer

Implements page replacement.

When memory becomes full,

Least Recently Used pages are evicted first.

---

# Index Layer

The indexing subsystem uses a B+ Tree.

Features

- Point Search
- Range Search
- Insert
- Delete
- Split
- Merge

Future

- Bulk Loading
- Prefix Compression

---

# Write Ahead Logging

Implements WAL protocol.

Every modification is logged before the actual page reaches disk.

Supports

- Recovery
- Crash Safety
- Durability

---

# Transaction Manager

Responsible for

- Begin
- Commit
- Abort
- Lock Acquisition
- Lock Release

Future

- MVCC
- Snapshot Isolation

---

# SQL Parser

Converts SQL text into executable syntax trees.

Pipeline

```
SQL

↓

Lexer

↓

Parser

↓

AST

↓

Executor
```

---

# Query Executor

Executes parsed queries.

Example execution path

```
SELECT * FROM users;

↓

Lexer

↓

Parser

↓

Executor

↓

B+ Tree

↓

Buffer Pool

↓

Disk
```

---

# Build Instructions

## Clone

```bash
git clone https://github.com/<your_username>/MYDB.git

cd MYDB
```

---

## Build

```bash
mkdir build

cd build

cmake ..

make -j
```

---

## Run

```bash
./mydb
```

---

# Running Tests

```bash
ctest
```

or

```bash
./mydb_tests
```

---

# Development Roadmap

## Phase 1

- [x] Project Setup
- [x] Page Class
- [x] Disk Manager
- [ ] Buffer Pool Manager
- [ ] LRU Replacer

---

## Phase 2

- [ ] B+ Tree
- [ ] Leaf Nodes
- [ ] Internal Nodes
- [ ] Page Splitting
- [ ] Merge

---

## Phase 3

- [ ] WAL
- [ ] Log Manager
- [ ] Recovery

---

## Phase 4

- [ ] Transactions
- [ ] Lock Manager
- [ ] Concurrency

---

## Phase 5

- [ ] SQL Lexer
- [ ] SQL Parser
- [ ] AST

---

## Phase 6

- [ ] Query Executor
- [ ] Query Optimizer
- [ ] Join Algorithms

---

# Learning Outcomes

This project explores many important computer science topics:

- Database Systems
- Operating Systems
- File Systems
- Storage Engines
- Memory Management
- Data Structures
- B+ Trees
- C++
- Object-Oriented Design
- Concurrency
- Synchronization
- System Design

---

# References

The implementation is inspired by concepts from:

- CMU 15-445 Database Systems (BusTub)
- PostgreSQL Source Code
- SQLite Source Code
- MySQL InnoDB
- Database System Concepts (Silberschatz, Korth & Sudarshan)
- Database Internals by Alex Petrov
- Designing Data-Intensive Applications by Martin Kleppmann

---

# Future Improvements

- Query Optimizer
- Cost-Based Planner
- Hash Index
- MVCC
- Parallel Query Execution
- Replication
- Distributed Storage
- Column Store
- Compression
- Bloom Filters
- Vectorized Execution

---

# License

This project is released under the MIT License.

---

# Author

**Sai Vinyas BS**

GitHub: https://github.com/VINYAS-BTW

LinkedIn: https://linkedin.com/in/sai-vinyas-bs-864510296

Portfolio: https://vinyas.vercel.app

---

## Project Vision

> "The best way to understand a database is to build one."

MYDB is a long-term educational project focused on exploring the internals of modern relational database systems through hands-on implementation in C++. The goal is not only to create a working database engine, but also to gain a deep understanding of the algorithms and systems that power production-grade databases.
