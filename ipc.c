/*  Universidade Federal de Uberlândia - UFU 
        Sistemas de Informação
    Trabalho Prático de Programação Computacional
            "Sistema de Saúde"
    
    OBJETIVOS   :   
                        1.  CADASTRO/AGENDAMENTO DE PACIENTES.
                            .   Ter uma variável com os horários vagos dentro de uma função para cada especialidade;
                            .   Caso o paciente opte por ortopedia, marcar cosulta para o ortopedista;
                            .   Caso o paciente opte por fisioterapia, marcar colsuta para o fisioterapeuta;
                            .   Caso o paciente opte por exame, marcar exame;            
                            .   Mostrar as informações do paciente e confirmar o agendamento;
                            .   Apresentar essas opções ao usuário e armazenar a escolhida, se disponível na struct dados_dos_pacientes;
                            .   Ordenar os dados dos pacientes em ordem alfabética e depois armazenar em um arquivo.
                        
                        2.  APRESENTAÇÃO DE CADASTROS/AGENDAMENTOS P/ ORTOPEDISTA. (juntamente ao horário)
                        3.  APRESENTAÇÃO DE CADASTROS/AGENDAMENTOS P/ FISIOTERAPEUTA. (juntamente ao horário)
                        4.  APRESENTAÇÃO DE CADASTROS/AGENDAMENTOS P/ EXAME. (juntamente ao horário)
                        5.  Correção dos Dados digitados. 
                        6.  CANCELAMENTO DE CONSULTA.
                        7.  Backup.
                        0.  SAIR. 
    AUTORES     :   
                    .   Antonio Cesar Ferreira Neves
                    .   Arthur Ferreira da Silva
                    .   Augusto Fernandes Macri
                    .   Gabriel Antonio de Oliveira Leite
                    .   Paula Fernanda Rosa do Nascimento
                    .   Renata Virna Lourenço Balbino
    Última Atualização  :   16/03/2022
    versão 0.07
*/
// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structs:

// Armazena os dados dos pacientes
typedef struct
{ 
    char nome[60];
    char  data_de_nascimento[16];
    char tipo_sanguineo[5];
    short int agendamento;
    char data_da_consulta[12]; 
    short int  horario_consulta;  
}
dados_dos_pacientes;

// Armazena os horários disponíveis em uma matriz tri-dimensional
typedef struct 
{
    short int horario_disponivel [12][31][24];
}
expediente;

// Funções:
void menu(void);

void cadastro(expediente profissoes_horarioatendimento[]);

void horario_expediente(expediente profissoes_horarioatendimento[]);

void mostra_opcao(int paciente, dados_dos_pacientes pacientes[] ,expediente profissoes_horarioatendimento[]);

void marcar_horario(dados_dos_pacientes pacientes[], expediente profissoes_horarioatendimento[], int paciente);

void mostra1(dados_dos_pacientes pacientes[], int paciente);

void verifica(int *paciente);

void ordenacao(dados_dos_pacientes pacientes[], int numero_pacientes);

int  crescente(dados_dos_pacientes *a, dados_dos_pacientes *b);

void armazena_horarios_emarquivo(expediente *agendamento);

void persistencia_dos_dados(dados_dos_pacientes pacientes[], int numero_pacientes);
 
void registro_dos_cadastros(short int opcao);

dados_dos_pacientes* ler_arquivo(short int opcao, int* quantidade_de_pacientes);

void dados_incorretos(void);

short int pesquisa(char nome[], dados_dos_pacientes pa[], int inicio, int fim );

void altera_dados(dados_dos_pacientes pacientes[], short int *opcao, int tamanho);

void cancelamento(void);

short int descobrindo_a_posicao_das_horas(short int horario_a_ser_revalidado);

void separa_o_dia_e_o_mes(char data_da_consulta[],   short int *dia,  short int *mes);

void escolhendo_qual_arquivo_tera_backup(void);

void backup(FILE *profissao, FILE *novo_arquivo);



int main()
{
    menu();  
}
void menu()
{    
    // Horarios vagos
    expediente *profissoes_horarioatendimento = NULL;   
    short int opcao; 
    
    while(1)
    {
        printf("===============================================================================================================================================\n\n");
        printf("\t\t\t\t\t\tSEJA BEM-VINDO AO SISTEMA DE SAÚDE");
        printf("\n\n===============================================================================================================================================\n\n");
        printf("\t[1] Cadastro\t");
        printf("\t\t\t[2] Registro dos cadastros Ortopedista\t");
        printf("\t[3] Registro dos cadastros Fisioterapeuta\t\n\n");
        printf("\t[4] Registro dos cadastros Exame");
        printf("\t[5] Registro de todas as consultas marcadas");
        printf("\t[6] Correção do nome digitado\n\n");
        printf("\t[7] Cancelamento da Consulta");
        printf("\t\t[8] Backup\n");
        printf("\n\t\t\t\t\t\t\t [0] Sair\n");
        printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------\n");
        
        printf("\nDigite o número da opção desejada:\n");
        scanf("%hd", &opcao);
        printf("\n");
        
        if(opcao == 1) cadastro(profissoes_horarioatendimento);
        if(opcao == 2) registro_dos_cadastros(1);
        if(opcao == 3) registro_dos_cadastros(2);
        if(opcao == 4) registro_dos_cadastros(3);
        if(opcao == 5) registro_dos_cadastros(0);
        if(opcao == 6) dados_incorretos(); 
        if(opcao == 7) cancelamento();
        if(opcao == 8) escolhendo_qual_arquivo_tera_backup(); 
        if(opcao == 0) return;
    }
}
// Cadastra os pacientes
void cadastro(expediente profissoes_horarioatendimento[])
{   
    // Alocação dinamica para os horarios das tres profissões
    profissoes_horarioatendimento  =  malloc(3 * sizeof(expediente));
    
    horario_expediente(profissoes_horarioatendimento);
    
    int numero_pacientes, paciente = 0; 
    
    printf("\n\tCADASTRO DE PACIENTES\n\n");
    printf("Digite quantos pacientes você deseja cadastrar:\n");
    scanf("%d" , &numero_pacientes);
    printf("\n");
    
    // Alocação dinamica para estrutura pacientes    
    dados_dos_pacientes *pacientes = NULL;
    pacientes = malloc(numero_pacientes  * sizeof(dados_dos_pacientes));  
    
    // Inicializando o castro dos pacientes
    if (numero_pacientes > 0)
    {
        for(paciente = 0; paciente < numero_pacientes; paciente ++)
        {           
            // Nome
            printf("Digite o nome completo do %dº paciente a ser cadastrado:\n", paciente + 1); 
            setbuf(stdin, NULL); 
            fgets(pacientes[paciente].nome,60,stdin); 
            printf("\n");        
            
            // Data de Nascimento:
            printf("Digite a data de nascimento no formato dias/meses/anos:\n"); 
            setbuf(stdin, NULL); 
            fgets(pacientes[paciente].data_de_nascimento, 16, stdin); 
            printf("\n");
            
            // Tipo Sanguíneo
            printf("Digite o tipo sanguineo do %dº paciente:\n", paciente + 1); 
            setbuf(stdin,NULL);         
            fgets(pacientes[paciente].tipo_sanguineo, 5, stdin);  
            printf("\n");
            
            printf("Digite o número da opção da qual deseja realizar um agendamento:\n"); 
            printf("\n[1]Ortepedista\t[2]Fisioterapeuta\t[3]Exame\n\n");
            scanf("%hd", &pacientes[paciente].agendamento); 
            
            // Trocando o \n por \0 que o fgets coloca
            pacientes[paciente].nome[strcspn(pacientes[paciente].nome, "\n")] = '\0';
            pacientes[paciente].tipo_sanguineo[strcspn(pacientes[paciente].tipo_sanguineo, "\n")] = '\0';
            pacientes[paciente].data_de_nascimento[strcspn(pacientes[paciente].data_de_nascimento, "\n")] = '\0';
            
            mostra_opcao(paciente, pacientes, profissoes_horarioatendimento); 
            
            mostra1(pacientes, paciente);  
            
            verifica(&paciente);
            
            sleep(2);
            
            system("clear");
        }
    
        ordenacao(pacientes,  numero_pacientes);
    
        armazena_horarios_emarquivo(profissoes_horarioatendimento);
    
        persistencia_dos_dados(pacientes, numero_pacientes);
    
        system("clear");
    
        // Liberação da memória alocada pela função malloc (L 173)
    
        free(profissoes_horarioatendimento);
        free(pacientes);
    }
}

// Atribuiu os horarios disponiveis dos expedientes a agendamento
void horario_expediente(expediente profissoes_horarioatendimento[])
{
    FILE *horario_atendimento_txt = fopen("Horarios_de_atendimento.txt","r");

  
    int verifica = 0;
    int quantidade_de_linhas = 0;
   
    if (horario_atendimento_txt != NULL)
    {    
        quantidade_de_linhas ++ ;
        
        while ((verifica = fgetc(horario_atendimento_txt)) != EOF)
        {
            if (verifica == '\n') quantidade_de_linhas ++;
            
        }
      
        fclose(horario_atendimento_txt);
    
    }
    
    else
    {
        quantidade_de_linhas = 0;
    }
    
        
    short int  profissional, mes, dia,horario;
    
    short int horario_de_atendimento = 8;
    const short int termino_do_horario_de_atendimento = 18;
    
    const short int ultimo_mes_do_ano = 11 , ultimo_dia_do_mes = 30, vinte_quatro_horas = 23;
    
    const short int fevereiro = 1, nao_existe = 0 ,dia_vinte_oito = 27 , dia_trinta = 29;
    const short int tem_apenas_30_dias[4] = {3 , 5 , 8 , 11};
    
    if(quantidade_de_linhas == 0)
    {   
        // dias_de_trabalho_das_profissoes = fopen("Horarios_de_atendimento.txt", "w");
        for(profissional = 0; profissional < 3; profissional++)
            for(mes = 0; mes <= ultimo_mes_do_ano; mes ++)
                for(dia = 0; dia <= ultimo_dia_do_mes; dia ++)
                    for(horario = 0; horario <= vinte_quatro_horas ; horario ++)
                    {                         
                        profissoes_horarioatendimento[profissional].horario_disponivel[mes][dia][horario] = horario_de_atendimento;
                                               
                        if(mes == fevereiro && dia > dia_vinte_oito)
                        {
                            profissoes_horarioatendimento[profissional].horario_disponivel[mes][dia][horario] = nao_existe;
                            break;
                        }
                                                
                        else if(dia == dia_trinta && (mes == tem_apenas_30_dias[0] || mes ==  tem_apenas_30_dias[1]|| mes == tem_apenas_30_dias[2] || mes == tem_apenas_30_dias[3] ) )
                        {
                            profissoes_horarioatendimento[profissional].horario_disponivel[mes][dia][horario] = nao_existe;
                            break;
                        }
                        
                        // Proxímo dia
                        else if(horario_de_atendimento == termino_do_horario_de_atendimento) 
                        {
                            horario_de_atendimento = 8; 
                            break;
                        } 
                        
                        // Passa para o próximo horário disponível
                        horario_de_atendimento ++; 
                        
                    }
    }
    
    else
    {
        FILE *dias_de_trabalho_das_profissoes = fopen("Horarios_de_atendimento.txt","r");
        
        for(profissional = 0; profissional < 3; profissional ++)
            for(mes = 0; mes < 12; mes ++)
                for(dia = 0; dia < 31; dia ++)  
                    for(horario = 0; horario < 24; horario ++)
                        fscanf(dias_de_trabalho_das_profissoes, "%hd\n",  &profissoes_horarioatendimento[profissional].horario_disponivel[mes][dia][horario]);
                         
        fclose(dias_de_trabalho_das_profissoes);
    }
   
            
}

// Mostra na tela o agendamento escolhido em cadastro e direciona para marcar o horario
void mostra_opcao(int paciente, dados_dos_pacientes pacientes[], expediente profissoes_horarioatendimento[])
{
    switch(pacientes[paciente].agendamento)
    {
        case 1:
            printf("\n---------------------------------------------------------------------------------------------------------\n");
            printf("\nAGENDANDO: Ortopedia\n\n"   );
            break;
        
        case 2:
            printf("\n---------------------------------------------------------------------------------------------------------\n");
            printf("\nAGENDANDO: Fisioterapia\n\n");
            break;
        
        case 3:
            printf("\n---------------------------------------------------------------------------------------------------------\n");
            printf("\nAGENDANDO: Exame\n\n"         );
            break;    
    }
    
    marcar_horario(pacientes, profissoes_horarioatendimento, paciente);
}

// Função para apresentar os horarios disponiveis
void marcar_horario(dados_dos_pacientes pacientes[], expediente profissoes_horarioatendimento[], int paciente)
{   
    // Armazenando horario da consulta ou exame
    char dia[4], mes[4]; 
    
    // Início do atendimento
    short int horario_expediente = 8;  
    short int horario_escolhido;
    
    while(1)    
    {  
        horario_expediente = 8;
        
        // Dia da consulta:
        printf("Digite o DIA do compromisso a ser agendado:\n"); 
        setbuf(stdin, NULL);  
        fgets(dia, 4, stdin); 
        printf("\n"); 
        
        // Mês da consulta: 
        printf("Digite o MÊS do compromisso a ser agendado:\n"); 
        setbuf(stdin, NULL);  
        fgets(mes, 4, stdin);
        
        // Tirando o \n
        dia[strcspn(dia, "\n")] = '\0';       
        mes[strcspn(mes, "\n")] = '\0'; 
        printf("\n");
        
        // Horário da consulta:
        short int contador_horas;
        printf("Nesta data, esses são os horarios disponíveis:\n\n");
        
        for(contador_horas = 0; contador_horas < 11; contador_horas ++) 
        {
            // Apresentação de todos os horários disponíveis de acordo com a data
            if(profissoes_horarioatendimento[pacientes[paciente].agendamento -1].horario_disponivel[atoi(mes) - 1][atoi(dia) - 1][contador_horas] != 0)
            {
                // mostra a posição do ponteiro e os horarios disponiveis
                printf("[%hd] %hd:00\t", contador_horas, horario_expediente);
                
                // Quebra de linha
                if (contador_horas == 5)  printf("\n");
            }
            
            // Fim do horário de expediente
            else if(horario_expediente >= 18) break;
            
            horario_expediente++;
        }        
        
        printf("\n\nDigite o número da opção do horário de agendamento:\n"); 
        scanf("%hd", &horario_escolhido);
        printf("\n");  
        
        // Caso  a opção seja valida
        if(profissoes_horarioatendimento[pacientes[paciente].agendamento - 1].horario_disponivel[atoi(mes) -1][atoi(dia) -1][horario_escolhido] != 0)   
        {
            strcat(strcpy(pacientes[paciente].data_da_consulta, dia), "/");
            strcat(pacientes[paciente].data_da_consulta, mes);
            
            // Armazenando na struct paciente o horario escolhido pelo usuario
            pacientes[paciente].horario_consulta =  profissoes_horarioatendimento[pacientes[paciente].agendamento - 1].horario_disponivel[atoi(mes) -1][atoi(dia) -1][horario_escolhido];
            profissoes_horarioatendimento[pacientes[paciente].agendamento - 1].horario_disponivel[atoi(mes) -1][atoi(dia) -1][horario_escolhido] = 0; 
            
            break;  
        }
    }
    
    return;
}

// Mostra os dados digitados na tela
void mostra1(dados_dos_pacientes pacientes[], int contador)
{
    // Apresentação dos dados preenchidos 
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\tINFORMAÇÕES DO %d° PACIENTE ",contador + 1);
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("\nNOME\t\t\t:\t%s\n", pacientes[contador].nome); 
    printf("DATA DE NASCIMENTO\t:\t%s\n", pacientes[contador].data_de_nascimento);   
    printf("TIPO SANGUÍNEO\t\t:\t%s \n",pacientes[contador].tipo_sanguineo);
    
    // Switch para alternar o compromisso de acordo com a escolha do usuário 
    switch(pacientes[contador].agendamento)
    {
        case    1   :   
            printf("ESPECIALIDADE\t\t:\tOrtopedista\n"     );
            break;
        
        case    2   :   
            printf("ESPECIALIDADE\t\t:\tFisioterapeuta\n"  );  
            break;
        
        case    3   :   
            printf("ESPECIALIDADE\t\t:\tExame\n");
            break;
    }
    
    printf("DATA AGENDADA\t\t:\t%s\n", pacientes[contador].data_da_consulta);    
    printf("HORÁRIO AGENDADO\t:\t%hd:00\n", pacientes[contador].horario_consulta);
    printf("\n---------------------------------------------------------------------------------------------------------\n");             
}

// Função para verificar se os dados foram digitados corretamente 
void verifica(int *contador)
{
    int digitou_corretamente;
    
    printf("\nOs dados estão corretos?\n\nDigite [1] para SIM e [2] para NÃO\n");
    scanf("%d", &digitou_corretamente);
    
    if(digitou_corretamente == 1) printf("\n\nCadastro realizado com sucesso!\n\n");
    
    else if(digitou_corretamente == 2)  *contador = *contador - 1;
    
    // Em caso de erro   
    else if(digitou_corretamente != 1 && digitou_corretamente != 2)
    {   
        while(digitou_corretamente != 1 && digitou_corretamente !=2)
        {   
            // Verificando novamente 
            printf("\n/**ERRO**\nPor favor, tente novamente!\n");
            
            // Segunda chance
            printf("\nOs dados estão corretos?\n\nDigite [1] para SIM e [2] para NÃO\n");
            
            scanf("%d", &digitou_corretamente);
            
            if(digitou_corretamente == 1)  
            {
                printf("\nCadastro realizado com sucesso!\n\n");
                break;
            }
            
            else if (digitou_corretamente == 2)
            {
                *contador = *contador - 1;
                break;  
            }
        }
    }
}

void ordenacao(dados_dos_pacientes pacientes[], int numero_pacientes)
{      
    qsort(pacientes, numero_pacientes, sizeof(dados_dos_pacientes), crescente);
}

// Função para função qsort
int  crescente(dados_dos_pacientes *a, dados_dos_pacientes *b)
{        
    return (strcmp(a->nome , b -> nome));
}

void armazena_horarios_emarquivo(expediente *agendamento)
{     
    FILE *dias_de_trabalho_das_profissoes = NULL;
    
    dias_de_trabalho_das_profissoes = fopen("Horarios_de_atendimento.txt", "w");
    
    short int profissao, mes, dia, horario;
    
    for(profissao = 0; profissao < 3; profissao ++)
        for(mes = 0; mes < 12; mes ++)
            for(dia = 0; dia < 31; dia ++)  
                for(horario = 0; horario < 24; horario ++)
                    fprintf(dias_de_trabalho_das_profissoes, "%hd\n", agendamento[profissao].horario_disponivel[mes][dia][horario]);
    
    fclose(dias_de_trabalho_das_profissoes);
}

// Armazenando os dados em arquivo
void persistencia_dos_dados(dados_dos_pacientes pacientes[], int numero_pacientes) 
{
    // Declaração de variaveis
    int contador = 0;
    
    // Ponteiro que aponta para os arquivos de cadastro
    FILE *arquivo_ortopedista = NULL, *arquivo_fisioterapeuta = NULL, *arquivo_exame = NULL;
    
    // Abrindo arquivos
    arquivo_ortopedista     =   fopen("Pacientes Ortopedista.txt", "at"           );
    arquivo_fisioterapeuta  =   fopen("Pacientes Fisioterapeuta.txt", "at"        );
    arquivo_exame           =   fopen("Pacientes marcados para exame.txt", "at"   );
    
    // Armazenando os dados dos pacientes em um txt
    for(contador = 0; contador <= numero_pacientes -1; contador ++)
    {   
        //Favor nao tirar o \n vai cagar o arquivo todo
        if(pacientes[contador].agendamento == 1)
        {   
            fprintf(arquivo_ortopedista, "%s\n", pacientes[contador].nome);
            fprintf(arquivo_ortopedista, "%s\n", pacientes[contador].data_de_nascimento);
            fprintf(arquivo_ortopedista, "%s\n", pacientes[contador].tipo_sanguineo);
            fprintf(arquivo_ortopedista, "%s\n", pacientes[contador].data_da_consulta);
            fprintf(arquivo_ortopedista, "%hd\n", pacientes[contador].horario_consulta);
        }
    
        else if(pacientes[contador].agendamento == 2)
        {
            fprintf(arquivo_fisioterapeuta, "%s\n", pacientes[contador].nome);
            fprintf(arquivo_fisioterapeuta, "%s\n", pacientes[contador].data_de_nascimento);
            fprintf(arquivo_fisioterapeuta, "%s\n", pacientes[contador].tipo_sanguineo);
            fprintf(arquivo_fisioterapeuta, "%s\n", pacientes[contador].data_da_consulta);
            fprintf(arquivo_fisioterapeuta, "%hd\n", pacientes[contador].horario_consulta);
        }
    
        else
        {
            fprintf(arquivo_exame, "%s\n", pacientes[contador].nome);
            fprintf(arquivo_exame, "%s\n", pacientes[contador].data_de_nascimento);
            fprintf(arquivo_exame, "%s\n", pacientes[contador].tipo_sanguineo);
            fprintf(arquivo_exame, "%s\n", pacientes[contador].data_da_consulta);
            fprintf(arquivo_exame, "%hd\n", pacientes[contador].horario_consulta);
        }
    }
    
    // Fechando arquivos
    fclose(arquivo_ortopedista);
    fclose(arquivo_fisioterapeuta);
    fclose(arquivo_exame);
}

void registro_dos_cadastros(short int opcao)
{       
    dados_dos_pacientes *pacientes = NULL;
    int quantidade_de_pacientes = 0;

    if(opcao != 0)
    {    
        
        pacientes = ler_arquivo(opcao, &quantidade_de_pacientes);
        
        free(pacientes);
    }

    else if(opcao == 0)
    {
        pacientes = ler_arquivo(1 , &quantidade_de_pacientes);
        free(pacientes);
        
        pacientes = ler_arquivo(2 , &quantidade_de_pacientes);
        free(pacientes);
        
        pacientes = ler_arquivo(3 , &quantidade_de_pacientes);
        free(pacientes);
    }
}

dados_dos_pacientes* ler_arquivo(short int opcao, int* quantidade_de_pacientes)
{
    FILE *arquivo = NULL;
    dados_dos_pacientes* pacientes = NULL;
    
    pacientes = malloc(sizeof(dados_dos_pacientes));
    
    short int agendamento = 0;        
    
    switch(opcao)
    {
      case 1 : 
        printf("\n\tRELATÓRIO DE AGENDAMENTOS - ORTOPEDIA\n\n");
        
        arquivo     =   fopen("Pacientes Ortopedista.txt", "rt");
        agendamento =   opcao;
        break;           
      
      case 2 :
        printf("\n\tRELATÓRIO DE AGENDAMENTOS - FISIOTERAPIA\n\n");
        
        arquivo     =   fopen("Pacientes Fisioterapeuta.txt", "rt");
        agendamento =   opcao;
        break;  
      
      case 3 :
        printf("\n\tRELATÓRIO DE AGENDAMENTOS - EXAME\n\n");
        
        arquivo     =   fopen("Pacientes marcados para exame.txt", "rt");
        agendamento =   opcao;
        break; 
    }
    
    // Se o arquivo estiver vazio   
    if(arquivo == NULL)
    {
        printf("Arquivo não encontrado!\n\n");
        
        return NULL;
    }
    
    int pessoa  = 0;
    while(fgets(pacientes[pessoa].nome, 60 ,arquivo) != NULL) 
    {           
        fgets(pacientes[pessoa].data_de_nascimento, 16, arquivo);
        fgets(pacientes[pessoa].tipo_sanguineo, 5 ,arquivo);
        fgets(pacientes[pessoa].data_da_consulta, 12, arquivo);
        fscanf(arquivo, "%hd\n", &pacientes[pessoa].horario_consulta);       
        
        pacientes[pessoa].agendamento = agendamento;
        
        // Tirando o \n
        pacientes[pessoa].nome[strcspn(pacientes[pessoa].nome, "\n")] = '\0';
        pacientes[pessoa].data_de_nascimento[strcspn(pacientes[pessoa].data_de_nascimento, "\n")] = '\0';
        pacientes[pessoa].tipo_sanguineo[strcspn(pacientes[pessoa].tipo_sanguineo, "\n")] = '\0';
        pacientes[pessoa].data_da_consulta[strcspn(pacientes[pessoa].data_da_consulta, "\n")] = '\0';
        
        if(strcmp(pacientes[pessoa].data_da_consulta, "Cancelado") != 0)
            mostra1(pacientes, pessoa);
        
        pessoa ++;

        
        // Aumenta o espaço reservado para o endereçamento dados_dos_pacientes
        pacientes = realloc(pacientes, sizeof(dados_dos_pacientes) * (pessoa + 1));
    }
    
    fclose(arquivo);
    
    *quantidade_de_pacientes = pessoa;
    
    return pacientes;
}

void dados_incorretos(void)
{    
    short int opcao;
    char nome[60];
    
    printf("Digite o numero da opcao de cadastro abaixo que você errou o nome do paciente\n");
    printf("[1] Ortopedista\t[2] Fisioterapeuta\t[3] Exame\n");
    scanf("%hd", &opcao);
    
    printf("Digite o nome do paciente:\n");
    setbuf(stdin, NULL);
    fgets(nome,60,stdin);
    
    printf("\n");
    nome[strcspn(nome, "\n")] = '\0';
    
    dados_dos_pacientes *pacientes;
    int quantidade_de_pacientes = 0;
    
    pacientes = ler_arquivo(opcao, &quantidade_de_pacientes);
    short int pessoa_posicao = pesquisa(nome, pacientes, 0, quantidade_de_pacientes );
    
    setbuf(stdin,NULL);
    
    if(pessoa_posicao == -1) printf("ERRO:\tPaciente não encontrado no sistema!\n\n");
    
    else
    {
        printf("Novo nome: ");
        fgets(nome,60,stdin);
        setbuf(stdin, NULL);
        
        nome[strcspn(nome, "\n")] = '\0';
        
        // Alterando
        strcpy(pacientes[pessoa_posicao].nome,nome);
        printf("Alterado com sucesso!\n");
        printf("\n\nCom as alterações: \n");
        
        mostra1(pacientes, pessoa_posicao);
    }
    
    altera_dados(pacientes, &opcao, quantidade_de_pacientes);
    
    free(pacientes);
}

// Realiza a busca sequencial
short int pesquisa(char *nome, dados_dos_pacientes pacientes[], int inicio, int fim )
{   
    short int i;     
    
    for(i = inicio; i < fim; i ++)
        if(strcmp(nome, pacientes[i].nome) == 0) return i;
    
    return -1;       
}

// Armazenando os dados em arquivo
void altera_dados(dados_dos_pacientes pacientes[], short int* opcao, int quantidade_de_pacientes) 
{
    int contador = 0;
    
    // Ponteiro que aponta para os arquivos de cadastro
    FILE *arquivo = NULL;
    
    // Abrindo arquivos
    if(*opcao == 1) arquivo     =   fopen("Pacientes Ortopedista.txt", "w"           );
    if(*opcao == 2) arquivo     =   fopen("Pacientes Fisioterapeuta.txt", "w"        );
    if(*opcao == 3) arquivo     =   fopen("Pacientes marcados para exame.txt", "w"   );
    
    // Armazenando os dados dos pacientes em um txt
    for(contador = 0; contador < quantidade_de_pacientes; contador ++)
    {  
        fprintf(arquivo, "%s\n", pacientes[contador].nome);
        fprintf(arquivo, "%s\n", pacientes[contador].data_de_nascimento);
        fprintf(arquivo, "%s\n", pacientes[contador].tipo_sanguineo);
        fprintf(arquivo, "%s\n", pacientes[contador].data_da_consulta);
        fprintf(arquivo, "%hd\n", pacientes[contador].horario_consulta);
    }

    // Fechando arquivos
    fclose(arquivo);
}

void cancelamento(void)
{
    short int opcao;
    
    printf("Por favor digite o numero da opção abaixo que o paciente deseja cancelar: \n");
    printf("[1] Ortopedia [2] Fisiterapia [3] Exame\n");
    scanf("%hd", &opcao);
    
    int quantidade_de_pacientes = 0;
    
    dados_dos_pacientes *pacientes;
    
    pacientes = ler_arquivo(opcao, &quantidade_de_pacientes);
    
    char nome[60];
    
    printf("Digite o  nome do paciente que deseja fazer o cancelamento\n");
    setbuf(stdin,NULL);
    
    fgets(nome,60,stdin);
    nome[strcspn(nome, "\n")] = '\0'; 
    
    short int paciente_consulta_cancelada = pesquisa(nome, pacientes, 0, quantidade_de_pacientes);
    
    
    char data_da_consulta[12] = {};
    strcpy(data_da_consulta, pacientes[paciente_consulta_cancelada].data_da_consulta); 
    
    short int dia, mes;
    separa_o_dia_e_o_mes(data_da_consulta, &dia, &mes);
    
    expediente *profissoes_horarioatendimento;
    profissoes_horarioatendimento = malloc(3 * sizeof(expediente) );
    
    horario_expediente(profissoes_horarioatendimento);

    short int posicao_a_ser_revalidada = descobrindo_a_posicao_das_horas(pacientes[paciente_consulta_cancelada].horario_consulta);
    
    profissoes_horarioatendimento[opcao - 1].horario_disponivel[mes - 1][dia - 1][posicao_a_ser_revalidada] = pacientes[paciente_consulta_cancelada].horario_consulta;
        
    armazena_horarios_emarquivo(profissoes_horarioatendimento);
        
    free(profissoes_horarioatendimento);
    
    strcpy(pacientes[paciente_consulta_cancelada].data_da_consulta, "Cancelado");
    altera_dados(pacientes, &opcao, quantidade_de_pacientes);
    
    printf("O Cancelamento da consulta do paciente %s\nFoi realizado com sucesso\n", pacientes[paciente_consulta_cancelada].nome);
    
    //Delay Para mostrar a mensagem
    sleep(5);
    
    system("clear");
    
    free(pacientes);
}


short int descobrindo_a_posicao_das_horas(short int horario_a_ser_revalidado)
{
    short int posicao_horas = 0, termino_expediente = 10; 
    short int atendimento = 8;
    
    for(posicao_horas = 0; posicao_horas <= termino_expediente; posicao_horas ++)
    {
        if(atendimento == horario_a_ser_revalidado) return posicao_horas;
                
        atendimento ++;
    }
}

void separa_o_dia_e_o_mes(char data_da_consulta[],   short int *dia,  short int *mes)
{
    int i = 0;
   
    *dia = (data_da_consulta[0]) - 48;
    *dia = (*dia * 10) + (data_da_consulta[1] - 48);
    
    *mes = (data_da_consulta[3] - 48);
    *mes = (*mes * 10) + (data_da_consulta[4] - 48);
   
}


void escolhendo_qual_arquivo_tera_backup(void)
{
    system("clear");
    
    short int opcao;
    
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    printf("Digite o número respectivo do arquivo que você deseja realizar o Backup.\n");
    printf("[1]Ortopedista [2]Fisioterapeuta [3] Exame\n\n");
    scanf("%hd", &opcao);
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    FILE *arquivo = NULL;
    FILE *novo_arquivo = NULL;
    
    switch (opcao)
    {
        case 1  :
            arquivo         =   fopen("Pacientes Ortopedista.txt", "r");
            novo_arquivo    =   fopen("Backup Ortopedista.txt", "at");
            break;
        
        case 2  :
            arquivo         =   fopen("Pacientes Fisioterapeuta.txt", "r");
            novo_arquivo    =   fopen("Backup Fisioterapeuta.txt", "at");
            break;
        
        case 3  : 
            arquivo         =   fopen("Pacientes marcados para exame.txt", "r");
            novo_arquivo    =   fopen("Backup exame.txt", "at");
            break;
    }
    
    backup(arquivo, novo_arquivo);

}

void backup(FILE *profissao, FILE *novo_arquivo)
{    
    dados_dos_pacientes pacientes;
    
    while(fgets(pacientes.nome, 60, profissao ) != NULL) 
    {           
        
        fgets(pacientes.data_de_nascimento, 16, profissao);
        fgets(pacientes.tipo_sanguineo, 5 , profissao);
        fgets(pacientes.data_da_consulta, 12, profissao);
        fscanf(profissao, "%hd\n", &pacientes.horario_consulta);       
        
        fprintf(novo_arquivo, "%s", pacientes.nome);
        fprintf(novo_arquivo, "%s", pacientes.data_de_nascimento);
        fprintf(novo_arquivo, "%s", pacientes.tipo_sanguineo);
        fprintf(novo_arquivo, "%s", pacientes.data_da_consulta);
        fprintf(novo_arquivo, "%hd\n",pacientes.horario_consulta);      
    }    
    
    fclose(novo_arquivo);
}