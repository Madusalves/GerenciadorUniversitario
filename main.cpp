#include "crow.h"
#include <vector>
#include <string>
#include <sstream>
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

vector<Participante> participantes;

int main() {
    crow::SimpleApp app;
    
    CROW_ROUTE(app, "/")([]() {
        return R"(
            <html>
            <head><title>Gerenciamento universitário</title></head>
            <body>
                <button><a href="/cadastro">Cadastrar</a></button>
                <button><a href="/alterar">Alterar</a></button>
                <button><a href="/inscrever">Inscrever</a></button>
            </body>
            </html>
        )";
        });
    // Página principal com formulário HTML
    CROW_ROUTE(app, "/cadastro")([]() {
        return R"(
            <html>
            <head><title>Cadastro de Participante</title></head>
            <body>
                <h1>Cadastrar</h1>
                <button><a href="/cadastro/participante">Participante</a></button>
                <button><a href="/cadastro/atividade">Atividade</a></button>
                <button><a href="/">Voltar</a></button>
            </body>
            </html>
        )";
    });
    
    CROW_ROUTE(app, "/cadastro/participante")([]() {
        return R"(
            <html>
            <head><title>Cadastro de Participante</title></head>
            <body>
                <h1>Cadastro de Participante</h1>
                <form action="/cadastro/participante" method="POST">
                    Nome: <input type="text" name="nome"><br><br>
                    Matrícula: <input type="text" name="matricula"><br><br>
                    Curso: <input type="text" name="curso"><br><br>
                    Semestre: <input type="number" name="semestre"><br><br>
                    E-mail: <input type="email" name="email"><br><br>
                    Celular: <input type="text" name="celular"><br><br>
                    Gênero: <input type="text" name="genero"><br><br>
                    Idade: <input type="number" name="idade"><br><br>
                    Tipo: <input type="text" name="tipoParticipante"><br><br>
                    Esportivo (1=Sim, 0=Não): <input type="text" name="esportivo"><br><br>
                    <input type="submit" value="Cadastrar">
                    <button><a href="/cadastro">Voltar</a></button>
                </form>
            </body>
            </html>
        )";
        });


    // Rota para processar o formulário e salvar o participante
    CROW_ROUTE(app, "/cadastro/participante").methods("POST"_method)
    ([](const crow::request& req) {
        Participante p;

        auto qs = req.get_body_params();
        p.nome = qs.get("nome") ? qs.get("nome") : "";
        p.matricula = qs.get("matricula") ? qs.get("matricula") : "";
        p.curso = qs.get("curso") ? qs.get("curso") : "";
        p.semestre = qs.get("semestre") ? atoi(qs.get("semestre")) : 0;
        p.email = qs.get("email") ? qs.get("email") : "";
        p.celular = qs.get("celular") ? qs.get("celular") : "";
        p.genero = qs.get("genero") ? qs.get("genero") : "";
        p.idade = qs.get("idade") ? atoi(qs.get("idade")) : 0;
        p.tipoParticipante = qs.get("tipoParticipante") ? qs.get("tipoParticipante") : "";
        p.participaDeAtividadesEsportivas = qs.get("esportivo") && string(qs.get("esportivo")) == "1";

        participantes.push_back(p);
        std::ostringstream os;
        os << "<html><body>";
        os << "<h1>Participante Cadastrado com Sucesso</h1>";
        os << "<p><strong>Nome:</strong> " << p.nome << "</p>";
        os << "<p><strong>Matrícula:</strong> " << p.matricula << "</p>";
        os << "<a href='/'>Voltar</a>";
        os << "</body></html>";

        return crow::response(os.str());
    });

    app.port(18080).multithreaded().run();
}