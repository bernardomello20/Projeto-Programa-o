//===== BIBLIOTECAS =====//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_NOME 100
#define VALOR_HORA_EXTRA 80

//===== STRUCTS =====//
typedef struct {
    int id;
    char nome[MAX_NOME];
} Funcionario;

typedef struct {
    int idFuncionario;
    int entrada;
    int saida;
    int horasExtras;
    int aprovado; // 1 = aprovado | 0 = negado
} Registro;

//===== VARIÁVEIS GLOBAIS =====//
Funcionario funcionarios[MAX];
int totalFuncionarios = 0;

//===== FUNÇÕES AUXILIARES =====//
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int funcionarioExiste(int id) {
    for (int i = 0; i < totalFuncionarios; i++)
        if (funcionarios[i].id == id)
            return 1;
    return 0;
}

char* obterNome(int id) {
    for (int i = 0; i < totalFuncionarios; i++)
        if (funcionarios[i].id == id)
            return funcionarios[i].nome;
    return "Desconhecido";
}

//===== CADASTRO =====//
void cadastrarFuncionario() {
    system("clear");
    printf("=== CADASTRAR FUNCIONARIO ===\n\n");

    if (totalFuncionarios >= MAX) {
        printf("Limite maximo atingido!\n");
        return;
    }

    int id;
    printf("ID: ");
    scanf("%d", &id);
    limparBuffer();

    if (funcionarioExiste(id)) {
        printf("ID ja existe!\n");
        return;
    }

    funcionarios[totalFuncionarios].id = id;

    printf("Nome: ");
    fgets(funcionarios[totalFuncionarios].nome, MAX_NOME, stdin);
    funcionarios[totalFuncionarios].nome[strcspn(funcionarios[totalFuncionarios].nome, "\n")] = 0;

    totalFuncionarios++;

    printf("\nFuncionario cadastrado!\n");
}

void listarFuncionarios() {
    system("clear");
    printf("=== FUNCIONARIOS CADASTRADOS ===\n\n");

    if (totalFuncionarios == 0) {
        printf("Nenhum cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalFuncionarios; i++) {
        printf("ID: %d | Nome: %s\n",
               funcionarios[i].id,
               funcionarios[i].nome);
    }
}

//===== CALCULAR HORAS EXTRAS =====//
int calcularExtras(int entrada, int saida) {
    int horas = saida - entrada;
    if (horas <= 8) return 0;

    horas -= 8;
    if (horas > 2) horas = 2;
    return horas;
}

//===== REGISTRAR HORAS =====//
void solicitarHoras() {
    system("clear");
    printf("=== SOLICITAR HORAS EXTRAS ===\n\n");

    if (totalFuncionarios == 0) {
        printf("Nenhum funcionario cadastrado.\n");
        return;
    }

    listarFuncionarios();
    int id, entrada, saida, aprovacao;

    printf("\nID do funcionário: ");
    scanf("%d", &id);

    if (!funcionarioExiste(id)) {
        printf("ID não encontrado!\n");
        return;
    }

    printf("Entrada (hora inteira): ");
    scanf("%d", &entrada);
    printf("Saida (hora inteira): ");
    scanf("%d", &saida);

    int horas = calcularExtras(entrada, saida);

    printf("\nGestor aprova as horas? (1=sim / 0=nao): ");
    scanf("%d", &aprovacao);

    Registro reg;
    reg.idFuncionario = id;
    reg.entrada = entrada;
    reg.saida = saida;
    reg.horasExtras = horas;
    reg.aprovado = aprovacao;

    FILE *arq = fopen("registros.txt", "a");

    fprintf(arq, "%d %d %d %d %d\n",
            reg.idFuncionario,
            reg.entrada,
            reg.saida,
            reg.horasExtras,
            reg.aprovado);

    fclose(arq);

    if (aprovacao)
        printf("\nHoras extras aprovadas (%dh)!\n", horas);
    else
        printf("\nHoras extras negadas!\n");
}

//===== RELATÓRIO INDIVIDUAL =====//
void relatorioIndividual() {
    system("clear");
    printf("=== RELATORIO INDIVIDUAL ===\n\n");

    if (totalFuncionarios == 0) {
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    listarFuncionarios();

    int id;
    printf("\nDigite o ID: ");
    scanf("%d", &id);

    FILE *arq = fopen("registros.txt", "r");
    if (!arq) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    Registro r;
    int total = 0;

    printf("\n--- REGISTROS DE %s ---\n\n", obterNome(id));

    while (fscanf(arq, "%d %d %d %d %d",
                  &r.idFuncionario,
                  &r.entrada,
                  &r.saida,
                  &r.horasExtras,
                  &r.aprovado) == 5) {

        if (r.idFuncionario == id) {
            printf("Entrada: %dh | Saida: %dh | Extras: %dh | %s\n",
                   r.entrada, r.saida, r.horasExtras,
                   r.aprovado ? "APROVADO" : "NEGADO");

            if (r.aprovado)
                total += r.horasExtras;
        }
    }

    fclose(arq);

    printf("\nTotal de horas extras: %d\n", total);
    printf("Valor total: R$%d\n", total * VALOR_HORA_EXTRA);
}

//===== RELATORIO GERAL =====//
void relatorioGeral() {
    system("clear");
    printf("=== RELATORIO GERAL ===\n\n");

    FILE *arq = fopen("registros.txt", "r");

    if (!arq) {
        printf("Nenhum registro encontrado.\n");
        return;
    }

    Registro r;

    while (fscanf(arq, "%d %d %d %d %d",
                  &r.idFuncionario,
                  &r.entrada,
                  &r.saida,
                  &r.horasExtras,
                  &r.aprovado) == 5) {

        printf("ID: %d | Nome: %s\n", r.idFuncionario, obterNome(r.idFuncionario));
        printf("Entrada: %dh | Saida: %dh\n", r.entrada, r.saida);
        printf("Horas extras: %dh\n", r.horasExtras);
        printf("Status: %s\n", r.aprovado ? "APROVADO" : "NEGADO");
        printf("---------------------------------\n");
    }

    fclose(arq);
}

//===== MENU PRINCIPAL =====//
int main() {
    int opcao;

    do {
        system("clear");
        printf("=== SISTEMA DE HORAS EXTRAS ===\n");
        printf("1 - Cadastrar funcionario\n");
        printf("2 - Listar funcionarios\n");
        printf("3 - Solicitar horas extras\n");
        printf("4 - Relatorio individual\n");
        printf("5 - Relatorio geral\n");
        printf("6 - Sair\n");
        printf("-> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarFuncionario(); break;
            case 2: listarFuncionarios(); break;
            case 3: solicitarHoras(); break;
            case 4: relatorioIndividual(); break;
            case 5: relatorioGeral(); break;
            case 6: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }

        printf("\nPressione ENTER para continuar...");
        limparBuffer();
        getchar();

    } while (opcao != 6);

    return 0;
}
