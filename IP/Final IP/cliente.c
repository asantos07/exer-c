#include "cliente.h"

void saque(user current){
    float money, notas;
    fflush(stdin);
    printf("Insira o valor a ser retirado:");
    scanf("%f", &money);
    current.saldo-=money;
    log_user('s', current.numero, money, 0);
    write_user(current, false);
    add_money(-1*money);
    for (notas=0; notas<money; notas++)
        printf("--------------\n    $$$$\n--------------\n");
}

void deposito(user current){
    float money;
    fflush(stdin);
    printf("Insira o valor a ser depositado:");
    scanf("%f", &money);
    current.saldo+=money;
    log_user('d', current.numero, money, 0);
    write_user(current, false);
    add_money(money);
}

void transfer(user current)
{
    char* destino;
    char opt;
    int valor;
    user destinatario;
    destinatario=aloc_user(destinatario);

    destino=(char*) calloc(1, sizeof(current.numero));

    printf("\033[2J");
    printf("\033[0;0H");
    printf("Insira o número da conta de destino do pagamento:");
    fgets_n(destino, sizeof(destino));
    printf("\n Quer rever seu saldo?");
    scanf("%c", &opt);
    if(opt=='S' && opt=='s')
        printf("\n Saldo Atual: %d", current.saldo);
    printf("\n Insira o valor da tranferencia:");
    scanf("%d", &valor);
    if(current.saldo<valor || valor>current.limite)
        printf("\n Operação Ilegal \t / Saldo Insuficiente \t/ Limite Atingido");
    else
    {
        current.saldo-=valor;
        write_user(current, false);
        read_user(destino, destinatario);
        destinatario.saldo+=valor;
        write_user(destinatario, false);
        log_user('t', destinatario.numero, valor, destino);
    }

    free_user(destinatario);
    free(destino);
}

void extrato(user current)
{
    char* filename;
    char* extrat;
    int i;
    printf("\033[2J");
    printf("\033[0;0H");
    printf("\n Imprimindo TODA a atividade em sua conta: \n");
    i=strlen(current.numero)+strlen(user_unique) + 4;
    filename= (char*) calloc(1, i);
    strcpy(filename, user_unique);
    strcat(filename, current.numero);
    strcat(filename, ".log");
    extrat=loadfile_str(filename);
    puts(extrat);
    free(filename);
    free(extrat);
}

void user_menu(user current)
{
    short opt=0;
    fflush(stdin);
    printf("\n -Login Efetuado com Sucesso-");
    printf("\033[2J");
    printf("\033[0;0H");
    sleep(3);
    do
    {
        printf("\033[2J");
        printf("\033[0;0H");
        printf("Escolha a operação a ser realizada: \n \t 1) Visualizar Saldo \n \t 2) Realizar Transferencia \n \t 3) Visualizar data de cadastro \n \t 4) Visualizar limite \n \t 5) Visualizar extrato \n \t 6) Realisar deposito \n \t 7) Realisar saque \n \t 0) Sair");
        scanf("%hi", &opt);
        switch (opt)
        {
        case 1:
            printf("Saldo Atual: %d", current.saldo);
            break;
        case 2:
            transfer(current);
            break;
        case 3:
            printf("Data de cadastro da conta: %s", current.data);
            break;
        case 4:
            printf("Limite de tranferencia da conta: %d", current.limite);
            break;
        case 5:
            extrato(current);
            break;
        case 6:
            deposito(current);
            break;
        case 7:
            saque(current);
            break;
        }
    }
    while(opt!=0);
}
