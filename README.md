# Sistema de Controle de Horas Extras — Linguagem C

Este projeto implementa um **sistema de gerenciamento de horas extras** desenvolvido em **Linguagem C**, utilizando `struct`, arquivos `.txt`, vetores e um menu interativo via terminal.

O sistema permite cadastrar funcionários, registrar horas extras, aprová-las ou negá-las, e gerar relatórios individuais ou gerais.

---

## Funcionalidades

### **Cadastro de Funcionários**
- Armazena ID e nome.
- Evita IDs duplicados.
- Suporta até 100 funcionários.

### **Solicitação de Horas Extras**
- Funcionário informa horário de entrada e saída.
- Sistema calcula quantas horas extras podem ser pagas:
  - Considera jornada base de **8h**
  - Máximo de **2h extras por dia**
- Gestor aprova ou nega o pedido.

### **Registro em Arquivo**
Todos os registros são armazenados em:# Projeto-Programa-o
