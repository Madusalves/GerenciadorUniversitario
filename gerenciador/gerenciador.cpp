#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <locale.h>
using namespace std;

struct Participante {
    string nome;
    string matricula;
    string curso;
    int semestre;
    string email;
    string celular;
    string genero;
    int idade;
    string tipoParticipante; 
    bool participaDeAtividadesEsportivas;
};

struct Atividade{
    string nomeAtividade;
    string tipoAtividade;
    string local;
    string data; 
    int hora;
    int vagasDisponiveis;
};

struct Incricao {
    string participanteNome;
    string participanteAtividade;
    string dataInscricao;
    string presencaConfirmada;
};
vector<Participante> participantes;
vector<Atividade> atividades; 
vector<Incricao> inscricoes;

void cadastrarParticipante() {
    Participante p;
    cout << "Nome: ";
    getline(cin, p.nome);
    
    cout << "Matrícula: ";
    getline(cin, p.matricula);
    
    cout << "Curso: ";
    getline(cin, p.curso);
    
    cout << "Semestre: ";
    cin >> p.semestre;
    cin.ignore();
    
    cout << "E-mail: ";
    getline(cin, p.email);
    
    cout << "Celular: ";
    getline(cin, p.celular);
    
    cout << "Gênero: ";
    getline(cin, p.genero);
    
    cout << "Idade: ";
    cin >> p.idade;
    cin.ignore();
    
    cout << "Tipo de Participante (organizador/palestrante/ouvinte): ";
    getline(cin, p.tipoParticipante);
    
    cout << "Participa de atividades esportivas? (1 para sim, 0 para não): ";
    cin >> p.participaDeAtividadesEsportivas;
    cin.ignore();
    
    participantes.push_back(p);
    
    cout << "Cadastro realizado com sucesso!\n";
}


void cadastrarAtividade() {
    Atividade a;
    cout << "Nome da Atividade: ";
    getline(cin, a.nomeAtividade);
    
    cout << "Tipo de Atividade: ";
    getline(cin, a.tipoAtividade);
    
    cout << "Local: ";
    getline(cin, a.local);
    
    cout << "Data (DD/MM/AAAA): ";
    getline(cin, a.data);
    
    cout << "Hora (HHMM): ";
    cin >> a.hora;
    cin.ignore();
    
    cout << "Vagas Disponíveis: ";
    cin >> a.vagasDisponiveis;
    cin.ignore();
    
    atividades.push_back(a);
    
    cout << "Atividade cadastrada com sucesso!\n";
}

void inscreverParticipante() {
    Incricao i;
    cout << "Nome do Participante: ";
    getline(cin, i.participanteNome);
    
    cout << "Atividade: ";
    getline(cin, i.participanteAtividade);
    
    cout << "Data da Inscrição (DD/MM/AAAA): ";
    getline(cin, i.dataInscricao);
    
    cout << "Presença Confirmada? (sim/não): ";
    getline(cin, i.presencaConfirmada);
    
    inscricoes.push_back(i); // Adiciona a inscrição ao vetor de inscrições
    
    cout << "Inscrição realizada com sucesso!\n";
}
// alterarParticipante buscando por matrícula
void alterarParticipante() {
    string matricula;
    cin.ignore();
    cout << "Digite a matrícula do participante: ";
    getline(cin, matricula);
    for (auto &p : participantes) { 
        // auto para deduzir o tipo de p
        // Verifica se a matrícula do participante corresponde à matrícula fornecida
        // & é usado para modificar o participante diretamente no vetor participantes
         // Se a matrícula for encontrada, atualiza os dados do participante
        if (p.matricula == matricula) {
            cout << "Novo nome: "; 
            getline(cin, p.nome);
            cout << "Novo curso: "; 
            getline(cin, p.curso);
            cout << "Novo semestre: "; 
            cin >> p.semestre; 
            cin.ignore();
            cout << "Novo e-mail: "; 
            getline(cin, p.email);
            cout << "Novo celular: "; 
            getline(cin, p.celular);
            cout << "Novo gênero: "; 
            getline(cin, p.genero);
            cout << "Nova idade: "; 
            cin >> p.idade; 
            cin.ignore();
            cout << "Novo tipo de participante: "; 
            getline(cin, p.tipoParticipante);
            cout << "Participa de Atividades Esportivas (1=Sim, 0=Não): "; 
            cin >> p.participaDeAtividadesEsportivas;
            cout << "Participante alterado com sucesso!\n";
            return;
        }
    }
    cout << "Participante não encontrado.\n";
}

// alterarAtividade buscando por nome da atividade
void alterarAtividade() {
    string nomeAtividade;
    cin.ignore();
    cout << "Digite o nome da atividade: ";
    getline(cin, nomeAtividade); // auto deduz o tipo de nomeAtividade, & é usado para modificar a atividade diretamente no vetor atividades
    for (auto &a : atividades) {
        if (a.nomeAtividade == nomeAtividade) {
            cout << "Novo nome da atividade: ";
            getline(cin, a.nomeAtividade);
            cout << "Novo tipo de atividade: ";
            getline(cin, a.tipoAtividade);
            cout << "Novo local: ";
            getline(cin, a.local);
            cout << "Nova data (DD/MM/AAAA): ";
            getline(cin, a.data);
            cout << "Nova hora (HHMM): ";
            cin >> a.hora;
            cin.ignore();
            cout << "Novas vagas disponíveis: ";
            cin >> a.vagasDisponiveis;
            cin.ignore();
            cout << "Atividade alterada com sucesso!\n";
            return;
        }
    }
    cout << "Atividade não encontrada.\n";
}

// alterarInscricao buscando por nome do participante e nome da atividade
void alterarInscricao() {
    string participanteNome, nomeAtividade;
    cin.ignore();
    cout << "Digite o nome do participante: "; 
    getline(cin, participanteNome);
    cout << "Digite o nome da atividade: ";
    getline(cin, nomeAtividade);
    for (auto &i : inscricoes) { // auto deduz o tipo de i, & é usado para modificar a inscrição diretamente no vetor inscricoes
        if (i.participanteNome == participanteNome && i.participanteAtividade == nomeAtividade) {
            cout << "Nova data da inscrição (DD/MM/AAAA): ";
            getline(cin, i.dataInscricao);
            cout << "Presença confirmada? (sim/não): ";
            getline(cin, i.presencaConfirmada);
            cout << "Inscrição alterada com sucesso!\n";
            return;
        }
    }
}

void menu(){
    int opcao;
    do {
        cout << "\nMenu:\n";
        cout << "1. Cadastrar Participante\n";
        cout << "2. Cadastrar Atividade\n";
        cout << "3. Inscrever Participante\n";
        cout << "4. Alterar Participante\n";
        cout << "5. Alterar Atividade\n";
        cout << "6. Alterar Inscrição\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;
        cin.ignore(); // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                cadastrarParticipante();
                break;
            case 2:
                cadastrarAtividade();
                break;
            case 3:
                inscreverParticipante();
                break;
            case 4:
                alterarParticipante();
                break;
            case 5:
                alterarAtividade();
                break;
            case 6:
                alterarInscricao();
                break;
            case 0:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 0);
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Configura o locale para português do Brasil
    menu();
    return 0;
}