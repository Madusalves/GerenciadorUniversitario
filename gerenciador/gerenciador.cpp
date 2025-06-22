#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
    
    inscricoes.push_back(i);
    
    cout << "Inscrição realizada com sucesso!\n";
}
