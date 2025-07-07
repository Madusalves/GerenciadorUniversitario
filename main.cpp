#include "crow.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
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
    bool participaEsporte = false;
    int idAtvEsp;
};
vector<Participante> participantes;


struct Atividade {
    string nomeAtividade;
    string tipoAtividade;
    string local;
    string data;
    string hora;
    int vagasDisponiveis;
    bool esportiva;
};
vector<Atividade> atividades;

struct Inscricao {
    string participanteNome;
    string participanteAtividade;
    string dataInscricao;
    int idParticipante;
    int idAtividade;
};
vector<Inscricao> inscricoes;
struct Tipo {
    int id;
    string tipo;
    int qtdAtvs = 0;
};
vector<Tipo> tipos;

vector<int> participantesInscritos;
vector<int> atividadesInscritos;
std::string formatarData(const std::string& dataISO) {
    if (dataISO.length() != 10) return "";

    std::string ano = dataISO.substr(2, 2);    
    std::string mes = dataISO.substr(5, 2);     
    std::string dia = dataISO.substr(8, 2);     

    return dia + "/" + mes + "/" + ano;
}
int main() {
    crow::SimpleApp app;
    //main
    CROW_ROUTE(app, "/")([]() {
        std::ostringstream os;
        os << "<html>\n"
            << "<head>\n"
            << "<title>Gerenciamento universitário</title>\n"
            << "<link rel='stylesheet' href='/static/style.css'>\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id='ms'>\n"
            << "<div id='menu'>\n"
            << "<h1 id='menutitle'>Menu</h1>\n"
            << "<button><a href='/cadastro'>Cadastrar</a></button>\n"
            << "<button><a href='/alterar'>Alterar</a></button>\n"
            << "<button><a href='/inscricao'>Inscrição</a></button>\n"
            << "<button><a href='/listar'>Listar</a></button>\n"
            << "</div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
        });

    //menu de cadastros
    CROW_ROUTE(app, "/cadastro")([]() {
        std::ostringstream os;
        os << "<html>\n"
            << "<head>\n"
            << "<link rel='stylesheet' href='/static/style.css'>\n"
            << "<title>Cadastro</title>\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id='ms'>\n"
            << "<div id='menu'>\n"
            << "<h1 id='menutitle'>Cadastrar</h1>\n"
            << "<button><a href='/cadastro/participante'>Participante</a></button>\n"
            << "<button><a href='/cadastro/atividade'>Atividade</a></button>\n"
            << "<button><a href='/cadastro/tipo'>Tipo</a></button>\n"
            << "<hr>\n"
            << "<button id='voltar'><a href='/'> &lt; Voltar</a></button>\n"
            << "</div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
        });

    //menu de alterações
    CROW_ROUTE(app, "/alterar")([]() {
        std::ostringstream os;
        os << "<html>\n"
            << "<head>\n"
            << "<title>Alterar</title>\n"
            << "<link rel='stylesheet' href='/static/style.css'>\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id='ms'>\n"
            << "<div id='menu'>\n"
            << "<h1 id='menutitle'>Alterar</h1>\n"
            << "<button><a href='/alterar/participante'>Participante</a></button>\n"
            << "<button><a href='/alterar/atividade'>Atividade</a></button>\n"
            << "<button><a href='/alterar/inscricao'>Inscrição</a></button>\n"
            << "<hr>\n"
            << "<button id='voltar'><a href='/'> &lt; Voltar</a></button>\n"
            << "</div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
        });

	//menu de inscrições
    CROW_ROUTE(app, "/inscricao")([]() {
        std::ostringstream os;
        os << "<html>\n"
            << "<head>\n"
            << "<title>Inscrição</title>\n"
            << "<link rel='stylesheet' href='/static/style.css'>\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id='ms'>\n"
            << "<div id='menu'>\n"
            << "<h1 id='menutitle'>Inscrição</h1>\n"
            << "<button><a href='/inscricao/participante'>Inscrever</a></button>\n"
            << "<button><a href='/inscricao/visualizar'>Ver inscrições</a></button>\n"
            << "<hr>\n"
            << "<button id='voltar'><a href='/'> &lt; Voltar</a></button>\n"
            << "</div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
        });

    CROW_ROUTE(app, "/listar")([]() {
        std::ostringstream os;
        os << "<html>\n"
            << "<head>\n"
            << "<title>Listar</title>\n"
            << "<link rel='stylesheet' href='/static/style.css'>\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id='ms'>\n"
            << "<div id='menu'>\n"
            << "<h1 id='menutitle'>Listar</h1>\n"
            << "<button><a href='/atividade/visualizar/tipo'>Atividades por tipo</a></button>\n"
            << "<hr>\n"
            << "<button id='voltar'><a href='/'> &lt; Voltar</a></button>\n"
            << "</div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
        });

	//menu visualizar inscrições
    CROW_ROUTE(app, "/inscricao/visualizar")([]() {
        std::ostringstream os;
        os << "<html>\n"
            << "<head>\n"
            << "<title>Visualizar inscrição</title>\n"
            << "<link rel=\"stylesheet\" href=\"/static/style.css\">\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id=\"ms\">\n"
            << "<div id=\"menu\">\n"
            << "<h1 id=\"menutitle\">Visualizar</h1>\n"
            << "<button><a href=\"/inscricao/visualizar/porparticipante\">Por participante</a></button>\n"
            << "<button><a href=\"/inscricao/visualizar/poratividade\">Por atividade</a></button>\n"
            << "<button><a href=\"/inscricao/visualizar/pordata\">Por data</a></button>\n"
            << "<button><a href=\"/inscricao/visualizar/esportivos\">Esportivos</a></button>\n"
            << "<hr>\n"
            << "<button id=\"voltar\"><a href=\"/inscricao\">&lt; Voltar</a></button>\n"
            << "</div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
        });
    
    //cadastro participante
    CROW_ROUTE(app, "/cadastro/participante")([]() {
        std::ostringstream os;
        os << "<html>\n"
            << "<head>\n"
            << "<link rel=\"stylesheet\" href=\"/static/style.css\">\n"
            << "<title>Cadastro participante</title>\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id=\"ms\">\n"
            << "<div id=\"containerform\">\n"
            << "<h1 id=\"menutitle\">Cadastro de participante</h1>\n"
            << "<form action=\"/cadastro/participante\" method=\"POST\">\n"
            << "<div id=\"inputsdiv\">\n"
            << "<div id=\"esquerda\">\n"
            << "<label>Nome: <input type=\"text\" name=\"nome\" required placeholder=\"Nome completo\"></label>\n"
            << "<label>Matrícula: <input type=\"text\" name=\"matricula\" required></label>\n"
            << "<label>Curso: <input type=\"text\" name=\"curso\" required></label>\n"
            << "<label>Semestre: <input type=\"number\" name=\"semestre\" required></label>\n"
            << "<label>E-mail: <input type=\"email\" name=\"email\" placeholder=\"email@gmail.com\" required></label>\n"
            << "</div>\n"
            << "<div id=\"direita\">\n"
            << "<label>Celular: <input type=\"text\" name=\"celular\" placeholder=\"(99) 99999-9999\" required></label>\n"
            << "<label>Gênero: <input type=\"text\" name=\"genero\" required></label>\n"
            << "<label>Idade: <input type=\"number\" name=\"idade\" required></label>\n"
            << "<label>Tipo: <input type=\"text\" name=\"tipoParticipante\" required></label>\n"
            << "</div>\n"
            << "</div>\n"
            << "<div id=\"botoes\">\n"
            << "<button id=\"voltar\"><a href=\"/cadastro\">&lt; Voltar</a></button>\n"
            << "<button type=\"submit\" value=\"Cadastrar\" style=\"cursor: pointer;\"><a>Cadastrar</a></button>\n"
            << "</div>\n"
            << "</form>\n"
            << "</div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
        });

	//processamento do cadastro de participante
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
        participantes.push_back(p);

        std::ostringstream os;
        os << "<html>\n"
            << "<head><title>Participante cadastrado</title>\n"
            << "<link rel='stylesheet' href='/static/style.css'>\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id='ms'>\n"
            << "<h1 id='menutitle' style='margin-bottom: 2.5vh'>Participante cadastrado com Sucesso</h1>\n"
            << "<div id='listagem'>\n"
            << "<div class='cardparticipante'>\n"
            << "<h1>" << p.nome << "</h1>\n"
            << "<h5>Matrícula: " << p.matricula << "</h5>\n"
            << "<hr>\n"
            << "<div class='infosparticipante'>\n"
            << "<div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div>\n"
            << "</div>\n"
            << "</div>\n"
            << "</div>\n"
            << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>"
            << "<button id='voltar'><a href='/cadastro'>&lt; Voltar</a></button></div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
            });

	//cadastro atividade
    CROW_ROUTE(app, "/cadastro/atividade")([]() {
        std::ostringstream os;
        os << "<html>\n"
            << "<head>\n"
            << "<link rel='stylesheet' href='/static/style.css'>\n"
            << "<title>Cadastro de Atividade</title>\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id='ms'>\n"
            << "<div id='containerform'>\n"
            << "<h1 id='menutitle'>Cadastro de atividade</h1>\n"
            << "<form action='/cadastro/atividade' method='POST'>\n"
            << "<div id='mid'>\n"
            << "<label style='width: 100% !important;'>Nome <input type='text' name='nome' style='width: 100% !important;'></label>\n"
            << "<label style='width: 100% !important;'>Tipo <select name='tipo' style='width: 100% !important;'>\n";

            for (const auto& t : tipos) {
                os << "<option value=\"" << t.tipo << "\">" << t.tipo << "</option>\n";
            }

			os << "</select></label>\n"
            << "<label style='width: 100% !important;'>Local <input type='text' name='local' style='width: 100% !important;'></label>\n"
            << "<label style='width: 100% !important;'>Data <input type='date' name='data' style='width: 100% !important;'></label>\n"
            << "<label style='width: 100% !important;'>Horário (HH:MM) <input type='text' name='hora' pattern='\\d{2}:\\d{2}' style='width: 100% !important;'></label>\n"
            << "<label style='width: 100% !important;'>Vagas disponíveis <input type='number' name='vagas' style='width: 100% !important;'></label>\n"
            << "<label style='width: 100% !important;'>Esportiva:\n"
            << "<div id='divradio'>\n"
            << "<div><input type='radio' name='esportiva' value='sim' required>Sim</div>\n"
            << "<div><input type='radio' name='esportiva' value='nao' required>Não</div>\n"
            << "</div>\n"
            << "</label>\n"
            << "<div id='botoes'>\n"
            << "<button id='voltar'><a href='/cadastro'>&lt; Voltar</a></button>\n"
            << "<button type='submit' value='Cadastrar' style='cursor: pointer;'><a>Cadastrar</a></button>\n"
            << "</div>\n"
            << "</div>\n"
            << "</form>\n"
            << "</div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
        });

	//processamento do cadastro de atividade
    CROW_ROUTE(app, "/cadastro/atividade").methods("POST"_method)
        ([](const crow::request& req) {
        Atividade a;
        Tipo t;
        auto qs = req.get_body_params();

        a.nomeAtividade = qs.get("nome") ? qs.get("nome") : "";
        a.tipoAtividade = qs.get("tipo") ? qs.get("tipo") : "";
        a.local = qs.get("local") ? qs.get("local") : "";
        string data = qs.get("data") ? qs.get("data") : "";
		a.data = formatarData(data);
        a.hora = qs.get("hora") ? qs.get("hora") : "";
        a.vagasDisponiveis = qs.get("vagas") ? atoi(qs.get("vagas")) : 0;
        a.esportiva = qs.get("esportiva") && string(qs.get("esportiva")) == "sim";
        atividades.push_back(a);

        for (auto& t : tipos) {
            if (t.tipo == a.tipoAtividade) {
				t.qtdAtvs++;
                break;
	        }
	    }

        std::ostringstream os;
        os << "<html>\n"
            << "<head><title>Atividade cadastrada</title>\n"
            << "<link rel='stylesheet' href='/static/style.css'>\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id='ms'>\n"
            << "<h1 id='menutitle' style='margin-bottom: 2.5vh'>Atividade cadastrada com Sucesso</h1>\n"
            << "<div id='listagem'>\n"
            << "<div class='cardparticipante'>\n"
            << "<h1>" << a.nomeAtividade << "</h1>\n"
            << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>\n"
            << "<hr>\n"
            << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div></div>\n"
            << "</div>\n"
            << "</div>\n"
            << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'><button id='voltar'><a href=' /cadastro'>< Voltar</a></button></div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
            });

	//cadastro tipo
    CROW_ROUTE(app, "/cadastro/tipo").methods("GET"_method, "POST"_method)
        ([](const crow::request& req) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>Tipo</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";
        //GET
        if (req.method == crow::HTTPMethod::GET) {
        
        os << "<section id='ms'>\n"
            << "<div id='containerform'>\n"
            << "<h1 id='menutitle'>Cadastro de tipo</h1>\n"
            << "<form action='/cadastro/tipo' method='POST'>\n"
            << "<div id='mid'>\n"
            << "<label style='width: 100% !important;'>Nome <input type='text' name='nome' style='width: 100% !important;' required></label>\n"
            << "<div id='botoes'>\n"
            << "<button id='voltar'><a href='/cadastro'>&lt; Voltar</a></button>\n"
            << "<button type='submit' value='Cadastrar' style='cursor: pointer;'><a>Cadastrar</a></button>\n"
            << "</div>\n"
            << "</div>\n"
            << "</form>\n"
            << "</div>\n"
            << "</section>\n";
            return crow::response(os.str());
        }
        //POST
        else {
            Tipo t;
            auto qs = req.get_body_params();

            for (const auto& tipo : tipos) {
                if (tipo.tipo == qs.get("nome")) {
                    std::ostringstream os;
                    os << "<div id='menu'>\n"
                       << "<h1 id='erro'>Esse tipo já existe!</h1>\n"
                       << "<button id='voltar'><a href='/cadastro/tipo'>&lt; Voltar</a></button>\n"
                       << "</div>\n"
                       << "</section>\n"
                       << "</body></html>\n";
                    return crow::response(os.str());
                }
			}

            t.tipo = qs.get("nome") ? qs.get("nome") : "";
			t.id = tipos.size();
			tipos.push_back(t);

            os << "<section id='ms'>\n"
				<< "<h1 id='menutitle' style='margin-bottom: 2.5vh'>Tipo cadastrado com Sucesso</h1>\n"
                << "<div id='listagem'>\n"
                << "<div class='cardparticipante'>\n"
                << "<h1>" << t.tipo << "</h1>\n"
                << "</div>\n"
                << "</div>\n"
                << "<div id='menu' style='margin-top: 3vh;width: 12vw; height: 5.5vh;'>\n"
                << "<button id='voltar'><a href='/cadastrar'>< Voltar</a></button>\n"
                << "</div>\n"
                << "</section>\n";
            return crow::response(os.str());
        }
            });
        tipos.push_back({ 0, "Palestra", 0 });
        tipos.push_back({ 1, "Oficina", 0 });
        tipos.push_back({ 2, "Competição", 0 });
        tipos.push_back({ 3, "Festa", 0 });
    
	//alterar participante
    CROW_ROUTE(app, "/alterar/participante")([](const crow::request& req) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>Alterar participante</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";

        const char* pesquisa_param = req.url_params.get("pesquisa");

        if (participantes.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Não há participantes cadastrados!</h1><button id='voltar'><a href='/alterar'>< Voltar</a></button></div></section>";
        }

        else {
            os << "<section id='ms'>";
            os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Alterar participante</h1>";
            os << "<div id='searchbar'>";
            os << "<form action='/alterar/participante' method='GET'>";

            int indice = 0;
            if (pesquisa_param) {

                std::string termo_pesquisa = pesquisa_param;
                
                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por matrícula...' value='" << termo_pesquisa << "' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";

                bool found_match = false;
                for (const auto& p : participantes) {
                    if (p.matricula == termo_pesquisa) {
                        os << "<div class='cardparticipante'>";
                        os << "<h1>" << p.nome << "</h1>";
                        os << "<h5>Matrícula: " << p.matricula << " | " << p.idade << " anos</h5>";
                        os << "<hr>";
                        os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div></div>";
                        os << "<div class='cardactions'><button><a href='/participante/" << indice << "' style='color: yellow;'>Alterar</a></button><button><a href='/participante/deletar/" << indice << "' style='color: red;'>Excluir</a></button></div>";
                        os << "</div>";
                        found_match = true;
                    }
                    indice++;
                }
                if (!found_match) {
                    os << "<p style='color: white; font-size:1.5vw;'>Nenhum participante encontrado com a matrícula: " << termo_pesquisa << "</p>";
                }

            }
            else {
                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por matrícula...' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";
                for (const auto& p : participantes) {
                    os << "<div class='cardparticipante'>";
                    os << "<h1>" << p.nome << "</h1>";
                    os << "<h5>Matrícula: " << p.matricula << " | " << p.idade << " anos</h5>";
                    os << "<hr>";
                    os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div></div>";
                    os << "<div class='cardactions'><button><a href='/participante/" << indice << "' style='color: yellow;'>Alterar</a></button><button><a href='/participante/deletar/" << indice << "' style='color: red;'>Excluir</a></button></div>";
                    os << "</div>";
                    indice++;
                }
            }
            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href=' /alterar'>< Voltar</a></button></div>";
        }

        os << "</body>";
        os << "</html>";
        return crow::response(os.str());
        });

	//alterar atividade
    CROW_ROUTE(app, "/alterar/atividade")([](const crow::request& req) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>Alterar atividade</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";

        const char* pesquisa_param = req.url_params.get("pesquisa");

        if (atividades.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Não há atividades cadastradas!</h1><button id='voltar'><a href='/alterar'>< Voltar</a></button></div></section>";
        }
        else {
            os << "<section id='ms'>";
            os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Alterar atividade</h1>";
            os << "<div id='searchbar'>";
            os << "<form action='/alterar/atividade' method='GET'>";

            int indice = 0;
            if (pesquisa_param) {

                std::string termo_pesquisa = pesquisa_param;

                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por nome...' value='" << termo_pesquisa << "' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";

                bool found_match = false;
                for (const auto& a : atividades) {
                    if (a.nomeAtividade == termo_pesquisa) {
                        os << "<div class='cardparticipante'>";
                        os << "<h1>" << a.nomeAtividade << "</h1>";
                        os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
                        os << "<hr>";
                        os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div><br></div>";
                        os << "<div class='cardactions'><button><a href='/atividade/" << indice << "' style='color: yellow;'>Alterar</a></button><button><a href='/atividade/deletar/" << indice << "' style='color: red;'>Excluir</a></button></div>";
                        os << "</div>";
                        found_match = true;
                    }
                    indice++;
                }
                if (!found_match) {
                    os << "<p style='color: white; font-size:1.5vw;'>Nenhuma atividade encontrado com o nome: " << termo_pesquisa << "</p>";
                }

            }
            else {
                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por matrícula...' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";
                for (const auto& a : atividades) {
                    os << "<div class='cardparticipante'>";
                    os << "<h1>" << a.nomeAtividade << "</h1>";
                    os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
                    os << "<hr>";
                    os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div><br></div>";
                    os << "<div class='cardactions'><button><a href='/atividade/" << indice << "' style='color: yellow;'>Alterar</a></button><button><a href='/atividade/deletar/" << indice << "' style='color: red;'>Excluir</a></button></div>";
                    os << "</div>";
                    indice++;
                }
            }
            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href=' /alterar'>< Voltar</a></button></div>";
        }

        os << "</body>";
        os << "</html>";
        return crow::response(os.str());
        });
	//alterar participante por índice
    CROW_ROUTE(app, "/participante/<int>").methods("GET"_method, "POST"_method)
        ([](const crow::request& req, int indiceVetor) {
        std::ostringstream os;

        int tamanho = participantes.size();
        if (indiceVetor < 0 || indiceVetor >= tamanho) {
            os << "<html>";
            os << "<head><title>Alterar Participante</title>";
            os << "<link rel='stylesheet' href='/static/style.css'></head>";
            os << "<body>";
            os << "<section id='ms'>";
            os << "<div id='menu'>";
            os << "<h1 id='erro'>Participante não encontrado</h1>";
            os << "<button id=\"voltar\"><a href='/alterar/participante'>Voltar</a></button>";
            os << "</div>";
            os << "</section>";
            os << "</body></html>";
            return crow::response(os.str());
        }
        else {
            //GET
            if (req.method == crow::HTTPMethod::GET) {
                const Participante& p = participantes[indiceVetor];
                std::ostringstream os;

                os << "<html>\n"
                    << "<head><link rel=\"stylesheet\" href=\"/static/style.css\">\n"
                    << "<title>Alterar participante</title>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<section id=\"ms\">\n"
                    << "<div id=\"containerform\">\n"
                    << "<h1 id=\"menutitle\">Alterar participante</h1>\n"
                    << "<form action=\"/participante/" << indiceVetor << "\" method=\"POST\">\n"
                    << "<div id=\"inputsdiv\">\n"
                    << "<div id=\"esquerda\">\n"
                    << "<label>Nome: <input value=\"" << p.nome << "\" type=\"text\" name=\"nome\" required placeholder=\"Nome completo\"></label>\n"
                    << "<label>Matrícula: <input value=\"" << p.matricula << "\" type=\"text\" name=\"matricula\" readonly required></label>\n"
                    << "<label>Curso: <input value=\"" << p.curso << "\" type=\"text\" name=\"curso\" required></label>\n"
                    << "<label>Semestre: <input value=\"" << p.semestre << "\" type=\"number\" name=\"semestre\" required></label>\n"
                    << "<label>E-mail: <input value=\"" << p.email << "\" type=\"email\" name=\"email\" placeholder=\"email@gmail.com\" required></label>\n"
                    << "</div>\n"
                    << "<div id=\"direita\">\n"
                    << "<label>Celular: <input value=\"" << p.celular << "\" type=\"text\" name=\"celular\" placeholder=\"(99) 99999-9999\" required></label>\n"
                    << "<label>Gênero: <input value=\"" << p.genero << "\" type=\"text\" name=\"genero\" required></label>\n"
                    << "<label>Idade: <input value=\"" << p.idade << "\" type=\"number\" name=\"idade\" required></label>\n"
                    << "<label>Tipo: <input value=\"" << p.tipoParticipante << "\" type=\"text\" name=\"tipoParticipante\" required></label>\n"
                    << "</div>\n"
                    << "</div>\n"
                    << "<div id=\"botoes\">\n"
                    << "<button id=\"voltar\"><a href=\"/alterar/participante\">< Voltar</a></button>\n"
                    << "<button type=\"submit\" value=\"alterar\" style=\"cursor: pointer;\"><a>Alterar</a></button>\n"
                    << "</div>\n"
                    << "</form>\n"
                    << "</div>\n"
                    << "</section>\n"
                    << "</body>\n"
                    << "</html>\n";
                return crow::response(os.str());
            }
			//POST
            else {
                const Participante& p = participantes[indiceVetor];
                std::ostringstream os;
                auto dadosPost = req.get_body_params();

                participantes[indiceVetor].nome = dadosPost.get("nome") ? dadosPost.get("nome") : p.nome;
                participantes[indiceVetor].matricula = dadosPost.get("matricula") ? dadosPost.get("matricula") : p.matricula;
                participantes[indiceVetor].curso = dadosPost.get("curso") ? dadosPost.get("curso") : p.curso;
                participantes[indiceVetor].semestre = dadosPost.get("semestre") ? atoi(dadosPost.get("semestre")) : p.semestre;
                participantes[indiceVetor].email = dadosPost.get("email") ? dadosPost.get("email") : p.email;
                participantes[indiceVetor].celular = dadosPost.get("celular") ? dadosPost.get("celular") : p.celular;
                participantes[indiceVetor].genero = dadosPost.get("genero") ? dadosPost.get("genero") : p.genero;
                participantes[indiceVetor].idade = dadosPost.get("idade") ? atoi(dadosPost.get("idade")) : p.idade;
                participantes[indiceVetor].tipoParticipante = dadosPost.get("tipoParticipante") ? dadosPost.get("tipoParticipante") : p.tipoParticipante;

                os << "<html>\n"
                    << "<head><title>Participante Alterado</title>\n"
                    << "<link rel='stylesheet' href='/static/style.css'>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<section id='ms'>\n"
                    << "<h1 id='menutitle' style='margin-bottom:2.5vh;'>Participante Alterado com Sucesso</h1>\n"
                    << "<div id='listagem'>\n"
                    << "<div class='cardparticipante'>\n"
                    << "<h1>" << participantes[indiceVetor].nome << "</h1>\n"
                    << "<h5>Matrícula: " << participantes[indiceVetor].matricula << "</h5>\n"
                    << "<hr>\n"
                    << "<div class='infosparticipante'>\n"
                    << "<div><p>" << participantes[indiceVetor].curso << "</p><p>" << participantes[indiceVetor].semestre << "° período</p></div>\n"
                    << "</div>\n"
                    << "</div>\n"
                    << "</div>\n"
                    << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'><button id='voltar'><a href=' /alterar'>< Voltar</a></button></div>\n"
                    << "</section>\n"
                    << "</body>\n"
                    << "</html>\n";
                return crow::response(os.str());
            }
        }
            });

			//deletar participante
    CROW_ROUTE(app, "/participante/deletar/<int>").methods("GET"_method, "POST"_method)
        ([](const crow::request& req, int indiceVetor) {
        std::ostringstream os;

        int tamanho = participantes.size();
        if (indiceVetor < 0 || indiceVetor >= tamanho) {
            os << "<html>";
            os << "<head><title>Alterar Participante</title>";
            os << "<link rel='stylesheet' href='/static/style.css'></head>";
            os << "<body>";
            os << "<section id='ms'>";
            os << "<div id='menu'>";
            os << "<h1 id='erro'>Participante não encontrado</h1>";
            os << "<button id=\"voltar\"><a href='/alterar/participante'>Voltar</a></button>";
            os << "</div>";
            os << "</section>";
            os << "</body></html>";
            return crow::response(os.str());
        }
        else {
            if (req.method == crow::HTTPMethod::GET) {
                const Participante& p = participantes[indiceVetor];
                std::ostringstream os;
                os << "<html>\n"
                    << "<head><link rel=\"stylesheet\" href=\"/static/style.css\">\n"
                    << "<title>Deletar participante</title>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<section id=\"ms\">\n"
                    << "<div id=\"containerform\">\n"
                    << "<h1 id=\"menutitle\">Deletar participante</h1>\n"
                    << "<p>Tem certeza que deseja deletar o participante <strong>" << p.nome << "</strong>?</p>\n"
                    << "<form action=\"/participante/deletar/" << indiceVetor << "\" method=\"POST\">\n"
                    << "<div id=\"botoes\">\n"
                    << "<button id=\"voltar\"><a href=\"/alterar/participante\">< Voltar</a></button>\n"
                    << "<button type=\"submit\" value=\"deletar\" style=\"cursor: pointer;\"><a>Deletar</a></button>\n"
                    << "</div>\n"
                    << "</form>\n"
                    << "</div>\n"
                    << "</section>\n"
                    << "</body>\n"
                    << "</html>\n";
                return crow::response(os.str());
            }
            else {
                participantes.erase(participantes.begin() + indiceVetor);
                os << "<html>\n"
                    << "<head><title>Participante Deletado</title>\n"
                    << "<link rel='stylesheet' href='/static/style.css'>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<section id='ms'>\n"

                    << "<div id='listagem'>\n"
                    << "<h1 id='menutitle'>Participante Deletado com Sucesso</h1>\n"
                    << "</div>\n"
                    << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'><button id='voltar'><a href='/alterar/participante'>< Voltar</a></button></div>\n"
                    << "</section>\n"
                    << "</body>\n"
                    << "</html>\n";
                return crow::response(os.str());
            }
        }
            });
	//deletar atividade
    CROW_ROUTE(app, "/atividade/<int>").methods("GET"_method, "POST"_method)
        ([](const crow::request& req, int indiceVetor) {
        std::ostringstream os;

        int tamanho = atividades.size();
        if (indiceVetor < 0 || indiceVetor >= tamanho) {
            os << "<html>";
            os << "<head><title>Alterar atividade</title>";
            os << "<link rel='stylesheet' href='/static/style.css'></head>";
            os << "<body>";
            os << "<section id='ms'>";
            os << "<div id='menu'>";
            os << "<h1 id='erro'>Atividade não encontrada</h1>";
            os << "<button id=\"voltar\"><a href='/alterar/atividade'>Voltar</a></button>";
            os << "</div>";
            os << "</section>";
            os << "</body></html>";
            return crow::response(os.str());
        }
        else {
            if (req.method == crow::HTTPMethod::GET) {
                const Atividade& a = atividades[indiceVetor];
                std::ostringstream os;

                os << "<html>\n"
                    << "<head>\n"
                    << "<link rel=\"stylesheet\" href=\"/static/style.css\">\n"
                    << "<title>cadastro atividade</title>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<section id=\"ms\">\n"
                    << "<div id=\"containerform\">\n"
                    << "<h1 id=\"menutitle\">Alterar atividade</h1>\n"
                    << "<form action=\"/atividade/" << indiceVetor << "\" method=\"POST\">\n"
                    << "<div id=\"mid\">\n"
                    << "<label style=\"width: 100% !important;\">Nome <input type=\"text\" name=\"nome\" value='" << a.nomeAtividade << "'style = \"width: 100% !important;\"></label>\n"
                    << "<label style='width: 100% !important;'>Tipo <select name='tipo' style='width: 100% !important;'>\n";
                    for (const auto& t : tipos) {
                        os << "<option value=\"" << t.tipo << "\">" << t.tipo << "</option>\n";
                    }
                    os << "</select></label>\n"
                    << "<label style=\"width: 100% !important;\">Local <input type=\"text\" name=\"local\" value='" << a.local << "' style=\"width: 100% !important;\"></label>\n"
                    << "<label style=\"width: 100% !important;\">Data <input type=\"date\" name=\"data\" value='" << a.data << "' style=\"width: 100% !important;\"></label>\n"
                    << "<label style=\"width: 100% !important;\">Horario (HH:MM) <input type=\"text\" value='" << a.hora << "' name=\"hora\" pattern=\"\\d{2}:\\d{2}\" style=\"width: 100% !important;\"></label>\n"
                    << "<label style=\"width: 100% !important;\">Vagas disponíveis <input type=\"number\" value='" << a.vagasDisponiveis << "'  name=\"vagas\" style=\"width: 100% !important;\"></label>\n"
                    << "<label style=\"width: 100% !important;\">Esportiva:\n"
                    << "    <div id=\"divradio\">\n"
                    << "        <div><input type=\"radio\" name=\"esportiva\" value=\"sim\" required"
                    << (a.esportiva ? " checked" : "") << ">Sim</div>\n"
                    << "        <div><input type=\"radio\" name=\"esportiva\" value=\"nao\" required"
                    << (!a.esportiva ? " checked" : "") << ">Não</div>\n"
                    << "    </div>\n"
                    << "</label>\n"
                    << "<div id=\"botoes\">\n"
                    << "<button id=\"voltar\"><a href=\"/alterar/atividade\">< Voltar</a></button>\n"
                    << "<button type=\"submit\" value=\"alterar\" style=\"cursor: pointer;\"><a>Alterar</a></button>\n"
                    << "</div>\n"
                    << "</div>\n"
                    << "</form>\n"
                    << "</div>\n"
                    << "</section>\n"
                    << "</body>\n"
                    << "</html>\n";

                return crow::response(os.str());
            }
            else {
                const Atividade& a = atividades[indiceVetor];
                std::ostringstream os;
                auto dadosPost = req.get_body_params();
                if (a.tipoAtividade != dadosPost.get("tipo")) {
                    for (auto& t : tipos) {
                        if (t.tipo == a.tipoAtividade) {
                            t.qtdAtvs--;
                        }
                    }
				}

                atividades[indiceVetor].nomeAtividade = dadosPost.get("nome") ? dadosPost.get("nome") : a.nomeAtividade;
                atividades[indiceVetor].tipoAtividade = dadosPost.get("tipo") ? dadosPost.get("tipo") : a.tipoAtividade;
                atividades[indiceVetor].local = dadosPost.get("local") ? dadosPost.get("local") : a.local;
                atividades[indiceVetor].data = dadosPost.get("data") ? dadosPost.get("data") : a.data;
                atividades[indiceVetor].hora = dadosPost.get("hora") ? dadosPost.get("hora") : a.hora;
                atividades[indiceVetor].vagasDisponiveis = dadosPost.get("vagas") ? atoi(dadosPost.get("vagas")) : a.vagasDisponiveis;
                atividades[indiceVetor].esportiva = dadosPost.get("esportiva") && std::string(dadosPost.get("esportiva")) == "sim";

                Tipo t;

                for (auto& t : tipos) {
                    if (t.tipo == a.tipoAtividade) {
                        t.qtdAtvs++;
                        break;
                    }
                }

                os << "<html>\n"
                    << "<head><title>Atividade alterada</title>\n"
                    << "<link rel='stylesheet' href='/static/style.css'>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<section id='ms'>\n"
                    << "<h1 id='menutitle' style='margin-bottom:2.5vh;'>Atividade alterada com sucesso</h1>\n"
                    << "<div id='listagem'>\n"
                    << "<div class='cardparticipante'>\n"
                    << "<h1>" << atividades[indiceVetor].nomeAtividade << "</h1>\n"
                    << "<h5>Vagas: " << atividades[indiceVetor].vagasDisponiveis << " | " << atividades[indiceVetor].data << " - " << atividades[indiceVetor].hora << " </h5>\n"
                    << "<hr>\n"
                    << "<div class='infosparticipante'><div><p>" << atividades[indiceVetor].tipoAtividade << "</p><p>" << atividades[indiceVetor].local << "</p></div><br></div>\n"
                    << "</div>\n"
                    << "</div>\n"
                    << "<div id='menu' style='margin-top: 3vh;width: 12vw; height: 5.5vh;'><button id='voltar'><a href='/alterar/atividade'>< Voltar</a></button></div>\n"
                    << "</section>\n"
                    << "</body>\n"
                    << "</html>\n";

                return crow::response(os.str());
            }
        }
            });

			//deletar atividade por índice
    CROW_ROUTE(app, "/atividade/deletar/<int>").methods("GET"_method, "POST"_method)
        ([](const crow::request& req, int indiceVetor) {
        std::ostringstream os;

        int tamanho = atividades.size();
        if (indiceVetor < 0 || indiceVetor >= tamanho) {
            os << "<html>";
            os << "<head><title>Alterar atividade</title>";
            os << "<link rel='stylesheet' href='/static/style.css'></head>";
            os << "<body>";
            os << "<section id='ms'>";
            os << "<div id='menu'>";
            os << "<h1 id='erro'>Atividade não encontrado</h1>";
            os << "<button id=\"voltar\"><a href='/alterar/atividade'>Voltar</a></button>";
            os << "</div>";
            os << "</section>";
            os << "</body></html>";
            return crow::response(os.str());
        }
        else {
            if (req.method == crow::HTTPMethod::GET) {
                const Atividade& a = atividades[indiceVetor];
                std::ostringstream os;
                os << "<html>\n"
                    << "<head><link rel=\"stylesheet\" href=\"/static/style.css\">\n"
                    << "<title>Deletar participante</title>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<section id=\"ms\">\n"
                    << "<div id=\"containerform\">\n"
                    << "<h1 id=\"menutitle\">Deletar atividade</h1>\n"
                    << "<p>Tem certeza que deseja deletar a atividade <strong>" << a.nomeAtividade << "</strong>?</p>\n"
                    << "<form action=\"/atividade/deletar/" << indiceVetor << "\" method=\"POST\">\n"
                    << "<div id=\"botoes\">\n"
                    << "<button id=\"voltar\"><a href=\"/alterar/atividade\">< Voltar</a></button>\n"
                    << "<button type=\"submit\" value=\"deletar\" style=\"cursor: pointer;\"><a>Deletar</a></button>\n"
                    << "</div>\n"
                    << "</form>\n"
                    << "</div>\n"
                    << "</section>\n"
                    << "</body>\n"
                    << "</html>\n";
                return crow::response(os.str());
            }
            else {
				
                for(auto& t : tipos) {
                    if (t.tipo == atividades[indiceVetor].tipoAtividade) {
                        t.qtdAtvs--;
                        break;
                    }
				}
                
				
                inscricoes.erase(std::remove_if(inscricoes.begin(), inscricoes.end(),
                    [indiceVetor](const Inscricao& i) { return i.idAtividade == indiceVetor; }),
                    inscricoes.end());


                atividades.erase(atividades.begin() + indiceVetor);
                os << "<html>\n"
                    << "<head><title>Atividade Deletada</title>\n"
                    << "<link rel='stylesheet' href='/static/style.css'>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<section id='ms'>\n"

                    << "<div id='listagem'>\n"
                    << "<h1 id='menutitle'>Atividade Deletada Com Sucesso</h1>\n"
                    << "</div>\n"
                    << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'><button id='voltar'><a href='/alterar/atividade'>< Voltar</a></button></div>\n"
                    << "</section>\n"
                    << "</body>\n"
                    << "</html>\n";
                return crow::response(os.str());
            }
        }
            });

	//inscrever participante
    CROW_ROUTE(app, "/inscricao/participante")([](const crow::request& req) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>Inscrever participante</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";

        const char* pesquisa_param = req.url_params.get("pesquisa");

        if (participantes.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Não há participantes cadastrados!</h1><button id='voltar'><a href='/inscricao'>< Voltar</a></button></div></section>";
        }
        else if (atividades.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Não há atividades cadastradas!</h1><button id='voltar'><a href='/inscricao'>< Voltar</a></button></div></section>";
        }
        else {
            os << "<section id='ms'>";
            os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Selecione um participante</h1>";
            os << "<div id='searchbar'>";
            os << "<form action='/inscricao/participante' method='GET'>";

            int indice = 0;
            if (pesquisa_param) {

                std::string termo_pesquisa = pesquisa_param;

                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por matrícula...' value='" << termo_pesquisa << "' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";


                bool found_match = false;

                for (const auto& p : participantes) {
                    if (p.matricula == termo_pesquisa) {
                        os << "<div class='cardparticipante'>";
                        os << "<h1>" << p.nome << "</h1>";
                        os << "<h5>Matrícula: " << p.matricula << " | " << p.idade << " anos</h5>";
                        os << "<hr>";
                        os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div></div>";
                        os << "<div class='cardactions'><button style='width:6vw;'><a href='/inscricao/participante/" << indice << "' style='color: green; '>Selecionar</a></button></div>";
                        os << "</div>";
                        found_match = true;
                    }
                    indice++;
                }
                if (!found_match) {
                    os << "<p style='color: white; font-size:1.5vw;'>Nenhum participante encontrado com a matrícula: " << termo_pesquisa << "</p>";
                }

            }
            else {
                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por matrícula...' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";
                for (const auto& p : participantes) {
                    os << "<div class='cardparticipante'>";
                    os << "<h1>" << p.nome << "</h1>";
                    os << "<h5>Matrícula: " << p.matricula << " | " << p.idade << " anos</h5>";
                    os << "<hr>";
                    os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div></div>";
                    os << "<div class='cardactions'><button style='width:6vw;' ><a href='/inscricao/participante/" << indice << "' style='color: green;'>Selecionar</a></button></div>";
                    os << "</div>";
                    indice++;
                }
            }
            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href=' /inscricao'>< Voltar</a></button></div>";
        }

        os << "</body>";
        os << "</html>";
        return crow::response(os.str());
        });

	//inscrever participante por índice
    CROW_ROUTE(app, "/inscricao/participante/<int>")
        ([](const crow::request& req, int indexParticipante) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>inscricao</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";

        const char* pesquisa_param = req.url_params.get("pesquisa");

        if (participantes.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Não há participantes cadastrados!</h1><button id='voltar'><a href='/inscricao'>< Voltar</a></button></div></section>";
        }
        else if (atividades.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Não há atividades cadastradas!</h1><button id='voltar'><a href='/inscricao'>< Voltar</a></button></div></section>";
        }
        else {
            os << "<section id='ms'>";
            os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Selecione uma atividade</h1>";
            os << "<div id='searchbar'>";
            os << "<form action='/inscricao/participante/" << indexParticipante << "' method='GET'>";
            vector<int> jaInscritos;
            int indiceI = 0;
            for (const auto& inscricao : inscricoes) {
                if (inscricao.idParticipante == indexParticipante) {
                    jaInscritos.push_back(inscricao.idAtividade);
                }
            }
            int indice = 0;
            if (pesquisa_param) {

                std::string termo_pesquisa = pesquisa_param;

                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por nome...' value='" << termo_pesquisa << "' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";
                bool found_match = false;
                for (const auto& a : atividades) {
                    if (std::find(jaInscritos.begin(), jaInscritos.end(), indice) != jaInscritos.end()) {
                        indice++;
                        continue; 
					}
                    if (a.nomeAtividade == termo_pesquisa) {
                        os << "<div class='cardparticipante'>";
                        os << "<h1>" << a.nomeAtividade << "</h1>";
                        os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
                        os << "<hr>";
                        os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div><br></div>";
                        os << "<div class='cardactions'><button style='width:6vw;'><a href='/inscricao/participante/" << indexParticipante << "/" << indice << "' style='color: green; '>Selecionar</a></button></div>";
                        os << "</div>";
                        found_match = true;
                    }
                    indice++;
                }
                if (!found_match) {
                    os << "<p style='color: white; font-size:1.5vw;'>Nenhuma atividade encontrado com o nome: " << termo_pesquisa << "</p>";
                }

            }
            else {
                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por nome...' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";
                for (const auto& a : atividades) {
                    if (std::find(jaInscritos.begin(), jaInscritos.end(), indice) != jaInscritos.end()) {
                        indice++;
                        continue;
                    }
                    os << "<div class='cardparticipante'>";
                    os << "<h1>" << a.nomeAtividade << "</h1>";
                    os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
                    os << "<hr>";
                    os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div><br></div>";
                    os << "<div class='cardactions'><button style='width:6vw;'><a href='/inscricao/participante/" << indexParticipante << "/" << indice << "' style='color: green; '>Selecionar</a></button></div>";
                    os << "</div>";
                    indice++;
                }
            }
            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href='/inscricao/participante'>< Voltar</a></button>";
        }

        os << "</body>";
        os << "</html>";
        return crow::response(os.str());
            });
	//inscrever participante por índice e atividade
    CROW_ROUTE(app, "/inscricao/participante/<int>/<int>").methods("GET"_method, "POST"_method)
        ([](const crow::request& req, int indexParticipante, int indexAtividade) {
        std::ostringstream os;
        Participante& p = participantes[indexParticipante];
        Atividade& a = atividades[indexAtividade];
        os << "<html>";
        os << "<head><title>inscricao</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";
        if (req.method == crow::HTTPMethod::GET) {
            os << "<section id='ms'>";
            os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Deseja inscrever?</h1>";
            os << "<div id='listagem'>";
            os << "<div class='cardparticipante'>";
            os << "<h1>" << p.nome << "</h1>";
            os << "<h5>Matrícula: " << p.matricula << " | " << p.idade << " anos</h5>";
            os << "<hr>";
            os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div></div>";
            os << "</div>";
            os << "<h1 id='menutitle'>EM</h1>";
            os << "<div class='cardparticipante'>";
            os << "<h1>" << a.nomeAtividade << "</h1>";
            os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
            os << "<hr>";
            os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div><br></div>";
            os << "</div>";
            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;'>";
            os << "<form action='/inscricao/participante/" << indexParticipante << "/" << indexAtividade << "' method='POST' style='display: flex; gap:2vw;'>";
            os << "<button id='voltar'><a href='/inscricao/participante/" << indexParticipante << "'>Cancelar</a></button>";
            os << "<button type='submit' value='inscrever' style='cursor: pointer;'><a>Inscrever</a></button>";
            os << "</form>";
            os << "</div>";
            os << "</section>";
            os << "</body>";
            os << "</html>";
            return crow::response(os.str());
        }
        else {
            if (a.vagasDisponiveis <= 0) {
                os << "<section id='ms'>\n"
                    << "<div id='menu'>\n"
                    << "<h1 id='erro'>Não há vagas disponíveis!</h1>\n"
                    << "<button id='voltar'><a href='/inscricao/participante/" << indexParticipante << "'>< Voltar</a></button>\n"
                    << "</div>\n"
                    << "</section>\n";
                return crow::response(os.str());
			}
            Inscricao i;
            i.participanteNome = p.nome;
            i.participanteAtividade = a.nomeAtividade;
            std::time_t agora = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            i.dataInscricao = (std::ostringstream{} << std::put_time(std::localtime(&agora), "%d/%m/%y")).str();
            i.idParticipante = indexParticipante;
            i.idAtividade = indexAtividade;
            inscricoes.push_back(i);
            if (a.esportiva) {
                p.participaEsporte = true;
                p.idAtvEsp = indexAtividade;
            };
			a.vagasDisponiveis--;
            os << "<section id='ms'>\n"
                << "<div id='listagem'>\n"
                << "<div class='cardparticipante'>\n"
                << "<h1>" << i.participanteNome << "</h1>\n"
                << "<h5>Data da inscrição: " << i.dataInscricao << "</h5>\n"
                << "<hr>\n"
                << "<div class='infosparticipante'><div><p>Atividade:</p><p>" << a.nomeAtividade << "</p></div><br></div>\n"
                << "</div>\n"
                << "</div>\n"
                << "<div id='menu' style='margin-top: 3vh;width: 12vw; height: 5.5vh;'>\n"
                << "<button id='voltar'><a href='/inscricao'>< Voltar</a></button>\n"
                << "</div>\n"
                << "</section>\n";
            return crow::response(os.str());
        }

            });
	//visualizar inscrições por participante
    CROW_ROUTE(app, "/inscricao/visualizar/porparticipante")
        ([](const crow::request& req) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>inscricao</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";

        const char* pesquisa_param = req.url_params.get("pesquisa");

        if (inscricoes.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Não há participantes inscritos!</h1><button id='voltar'><a href='/inscricao/visualizar'>< Voltar</a></button></div></section>";
        }
        else {
            os << "<section id='ms'>";
            os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Buscar por participante</h1>";
            os << "<div id='searchbar'>";
            os << "<form action='/inscricao/visualizar/porparticipante' method='GET'>";


            participantesInscritos.clear();
            for (const auto& i : inscricoes) {
                participantesInscritos.push_back(i.idParticipante);
            }

            int indice = 0;
            if (pesquisa_param) {

                std::string termo_pesquisa = pesquisa_param;

                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por matrícula...' value='" << termo_pesquisa << "' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";


                bool found_match = false;

                for (const auto& p : participantes) {
                    if (p.matricula == termo_pesquisa) {
                        if (std::count(participantesInscritos.begin(), participantesInscritos.end(), indice) > 0) {
                            os << "<div class='cardparticipante'>";
                            os << "<h1>" << p.nome << "</h1>";
                            os << "<h5>Matrícula: " << p.matricula << " | " << p.idade << " anos</h5>";
                            os << "<hr>";
                            os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div></div>";
                            os << "<div class='cardactions'><button style='width:6vw;'><a href='/inscricao/visualizar/participante/" << indice << "' style='color: green; '>Selecionar</a></button></div>";
                            os << "</div>";
                            found_match = true;
                        }
                    }
                    indice++;
                }
                if (!found_match) {
                    os << "<p style='color: white; font-size:1.5vw;'>Nenhum participante encontrado com a matrícula: " << termo_pesquisa << "</p>";
                }

            }
            else {
                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por matrícula...' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";

                for (const auto& p : participantes) {
                    if (std::count(participantesInscritos.begin(), participantesInscritos.end(), indice) > 0) {
                        os << "<div class='cardparticipante'>";
                        os << "<h1>" << p.nome << "</h1>";
                        os << "<h5>Matrícula: " << p.matricula << " | " << p.idade << " anos</h5>";
                        os << "<hr>";
                        os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div></div>";
                        os << "<div class='cardactions'><button style='width:6vw;'><a href='/inscricao/visualizar/porparticipante/" << indice << "' style='color: green; '>Selecionar</a></button></div>";
                        os << "</div>";
                    }
                    indice++;
                }
            }
            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href=' /inscricao/visualizar'>< Voltar</a></button></div>";
        }

        os << "</body>";
        os << "</html>";
        return crow::response(os.str());
            });
	//visualizar inscrições por participante por índice
    CROW_ROUTE(app, "/inscricao/visualizar/porparticipante/<int>")([](const crow::request& req, int index) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>atividades inscritas</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";

        const Participante& p = participantes[index];

        os << "<section id='ms'>";
        os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Inscrições de: " << p.nome << "</h1>";

        atividadesInscritos.clear();
        for (const auto& i : inscricoes) {
            if (i.idParticipante == index)
                atividadesInscritos.push_back(i.idAtividade);
        }

        int indice = 0;
        os << "<div id='listagem'>";
        for (const auto& a : atividades) {
            if (std::count(atividadesInscritos.begin(), atividadesInscritos.end(), indice) == 0) {
                continue;
            }
            os << "<div class='cardparticipante'>";
            os << "<h1>" << a.nomeAtividade << "</h1>";
            os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
            os << "<hr>";
            os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div></div>";
            os << "</div>";
            indice++;
        }

        os << "</div>";
        os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
        os << "<button id='voltar'><a href=' /inscricao/visualizar/porparticipante'>< Voltar</a></button></div>";


        os << "</body>";
        os << "</html>";
        return crow::response(os.str());
        });
	//visualizar inscrições por atividade
    CROW_ROUTE(app, "/inscricao/visualizar/poratividade")
        ([](const crow::request& req) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>inscricao</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";

        const char* pesquisa_param = req.url_params.get("pesquisa");

        if (atividades.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Não há atividades cadastradas!</h1><button id='voltar'><a href='/inscricao/visualizar'>< Voltar</a></button></div></section>";
        }
        else {
            os << "<section id='ms'>";
            os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Visualizar por atividade</h1>";
            os << "<div id='searchbar'>";
            os << "<form action='/alterar/atividade' method='GET'>";

            int indice = 0;
            if (pesquisa_param) {

                std::string termo_pesquisa = pesquisa_param;

                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por nome...' value='" << termo_pesquisa << "' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";

                bool found_match = false;
                for (const auto& a : atividades) {
                    if (a.nomeAtividade == termo_pesquisa) {
                        os << "<div class='cardparticipante'>";
                        os << "<h1>" << a.nomeAtividade << "</h1>";
                        os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
                        os << "<hr>";
                        os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div><br></div>";
                        os << "<div class='cardactions'><button style='width:6vw;'><a href='/inscricao/visualizar/poratividade/" << indice << "' style='color: green;'>Selecionar</a></button></div>";
                        os << "</div>";
                        found_match = true;
                    }
                    indice++;
                }
                if (!found_match) {
                    os << "<p style='color: white; font-size:1.5vw;'>Nenhuma atividade encontrado com o nome: " << termo_pesquisa << "</p>";
                }

            }
            else {
                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por nome...' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";

                for (const auto& a : atividades) {
                    os << "<div class='cardparticipante'>";
                    os << "<h1>" << a.nomeAtividade << "</h1>";
                    os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
                    os << "<hr>";
                    os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div></div>";
                    os << "<div class='cardactions'><button style='width:6vw;'><a href='/inscricao/visualizar/poratividade/" << indice << "' style='color: green;'>Selecionar</a></button></div>";
                    os << "</div>";
                    indice++;
                }

            }
            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href=' /inscricao/visualizar'>< Voltar</a></button></div>";
            os << "</body>";
            os << "</html>";
        }

        return crow::response(os.str());
            });
	//visualizar inscrições por atividade por índice
    CROW_ROUTE(app, "/inscricao/visualizar/poratividade/<int>")([](const crow::request& req, int index) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>participantes inscritos</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";


        const Atividade& a = atividades[index];

        os << "<section id='ms'>";
        os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Inscrito(s) em: " << a.nomeAtividade << "</h1>";

        participantesInscritos.clear();
        for (const auto& i : inscricoes) {
            if (i.idAtividade == index) {
                participantesInscritos.push_back(i.idParticipante);
                cout << i.idParticipante;
            }

        }

        if (participantesInscritos.empty()) {
            os << "<div id='listagem'><p style='color: white; font-size:1.5vw;'>Nenhum participante inscrito nesta atividade.</p></div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href=' /inscricao/visualizar/poratividade'>< Voltar</a></button></div>";

        }
        else {

            int indice = 0;
            os << "<div id='listagem'>";
            for (const auto& p : participantes) {
                if (std::count(participantesInscritos.begin(), participantesInscritos.end(), indice) == 0) {
                    continue;
                }
                os << "<div class='cardparticipante'>";
                os << "<h1>" << p.nome << "</h1>";
                os << "<h5>Matrícula: " << p.matricula << " | " << p.idade << " anos</h5>";
                os << "<hr>";
                os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div></div>";

                os << "</div>";
                indice++;
            }

            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href=' /inscricao/visualizar/poratividade'>< Voltar</a></button></div>";


            os << "</body>";
            os << "</html>";
        }
        return crow::response(os.str());
        });
	//visualizar inscritos em atividades esportivas
    CROW_ROUTE(app, "/inscricao/visualizar/esportivos")
        ([](const crow::request& req) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>inscricao</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";



        if (inscricoes.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Não há inscritos!</h1><button id='voltar'><a href='/inscricao/visualizar'>< Voltar</a></button></div></section>";
        }
        else {
            bool match = false;
            os << "<section id='ms'>";
            os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Inscritos em atividades esportivas</h1>";
            os << "<div id='listagem'>";

            for (const auto& p : participantes) {


                if (p.participaEsporte) {
                    const Atividade& a = atividades[p.idAtvEsp];
                    os << "<div class='cardparticipante'>";
                    os << "<h1>" << p.nome << "</h1>";
                    os << "<h5>Matrícula: " << p.matricula << " | " << p.idade << " anos</h5>";
                    os << "<hr>";
                    os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div><br><p>Inscrito em: " << a.nomeAtividade << "</p></div>";
                    os << "</div>";
                    match = true;
                }
            }
            if (!match) {
                os << "<p style='color: white; font-size:1.5vw;'>Nenhum participante inscrito em atividades esportivas.</p>";
            }


            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href=' /inscricao/visualizar'>< Voltar</a></button></div>";
            os << "</body>";
            os << "</html>";
        }

        return crow::response(os.str());
            });
	//visualizar atividades por tipo
    CROW_ROUTE(app, "/atividade/visualizar/tipo")
        ([](const crow::request& req) {
		std::ostringstream os;

        os << "<html><head><title>Atividades</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";
        os << "<section id='ms'>";
        if (atividades.empty()) {
            os << "<html><head><title>Atividades por Tipo</title></head><body>";
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Não há atividades cadastradas!</h1><button id='voltar'><a href='/inscricao'>Voltar</a></button></div></section>";
            os << "</body></html>";
            return crow::response(os.str());
		}
        
		os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Atividades por Tipo</h1>";
		os << "<div id='listagem'>";
        for (const auto& t : tipos) {
			if (t.qtdAtvs == 0) continue;
            os << "<div class='cardparticipante'>";
            os << "<h1>Tipo: " << t.tipo << "</h1>";
            os << "<h5>Atividades registradas: " << t.qtdAtvs << "</h5>";
            os << "<hr>";
            os << "<div class='cardactions'><button style='width:6vw;'><a href='/atividade/visualizar/tipo/" << t.id << "' style='color: green; '>Selecionar</a></button></div>";
            os << "</div>";
        }
		os << "</div>";
		os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
		os << "<button id='voltar'><a href='/inscricao'>Voltar</a></button>";

        return crow::response(os.str());
            });
	//visualizar atividades por tipo por índice
    CROW_ROUTE(app, "/atividade/visualizar/tipo/<int>").methods("GET"_method, "POST"_method)
        ([](const crow::request& req, int indiceVetor) {
        std::ostringstream os;
		os << "<html>";
		os << "<head><title>Atividades por Tipo</title>";
		os << "<link rel='stylesheet' href='/static/style.css'></head>";
		os << "<body>";
		os << "<section id='ms'>";
        if (indiceVetor > tipos.size() - 1 || indiceVetor < 0) {
            os << "<html><head><title>Atividades por Tipo</title></head><body>";
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Esse tipo não existe</h1><button id='voltar'><a href='/inscricao'>Voltar</a></button></div></section>";
            os << "</body></html>";
            return crow::response(os.str());
		}
		os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Atividades do tipo: " << tipos[indiceVetor].tipo << "</h1>";
		os << "<div id='listagem'>";
        for (const auto& a : atividades) {
            if (a.tipoAtividade == tipos[indiceVetor].tipo) {
                os << "<div class='cardparticipante'>";
                os << "<h1>" << a.nomeAtividade << "</h1>";
                os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
                os << "<hr>";
                os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div><br></div>";
                os << "</div>";
            }
		}
		os << "</div>";
		os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
		os << "<button id='voltar'><a href='/atividade/visualizar/tipo'>Voltar</a></button>";
        return crow::response(os.str());
            });
	//alterar inscrição
    CROW_ROUTE(app, "/alterar/inscricao")([](const crow::request& req) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>Alterar inscrição</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";

        const char* pesquisa_param = req.url_params.get("pesquisa");

        os << "<section id='ms'>";
        if (inscricoes.empty()) {
            os << "<div id='menu'><h1 id='erro'>Não há inscrições cadastradas!</h1>";
            os << "<button id='voltar'><a href='/alterar'>Voltar</a></button>";
            os << "</section></body></html>";
            return crow::response(os.str());
        }

        os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Alterar inscrição</h1>";
        os << "<div id='searchbar'>";
        os << "<form action='/alterar/inscricao' method='GET'>";
        os << "<input type='search' name='pesquisa' placeholder='Pesquisar por nome ou matrícula...'";

        std::string termo_pesquisa;
        if (pesquisa_param) {
            termo_pesquisa = pesquisa_param;
            os << " value='" << termo_pesquisa << "'";
        }
        os << " required>";
        os << "</form></div>";

        os << "<div id='listagem'>";

        bool encontrou = false;
        int indicep = 0;

        for (const auto& i : inscricoes) {
            if (i.idParticipante >= participantes.size() || i.idAtividade >= atividades.size()) {
                continue; 
            }
            const auto& p = participantes[i.idParticipante];
            const auto& a = atividades[i.idAtividade];

            bool exibir = false;

            if (pesquisa_param) {
                if (p.matricula.find(termo_pesquisa) != std::string::npos ||
                    a.nomeAtividade.find(termo_pesquisa) != std::string::npos) {
                    exibir = true;
                }
            }
            else {
                exibir = true;
            }

            if (exibir) {
                os << "<div class='cardparticipante'>";
                os << "<h1>" << p.nome << "</h1>";
                os << "<h5>Matrícula:" << p.matricula << " | " << p.idade << " anos</h5>";
                os << "<hr>";
                os << "<div class='infosparticipante'><div><p>Inscrito em: " << a.nomeAtividade << "</p><p>" << a.tipoAtividade << "</p></div><br><p>Data inscrição: " << i.dataInscricao << "</p></div>";
                os << "<div class='cardactions'><button><a href='/alterar/inscricao/" << indicep << "' style='color: yellow;'>Alterar</a></button><button><a href='/inscricao/deletar/" << indicep << "' style='color: red;'>Excluir</a></button></div>";
                os << "</div>";
                encontrou = true;
            }
            indicep++;
        }

        if (pesquisa_param && !encontrou) {
            os << "<h1 id='erro'>Nenhuma inscrição encontrada!</h1>";
        }

        os << "</div>"; 
        os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
        os << "<button id='voltar'><a href='/alterar'>Voltar</a></button>";
        os << "</section></body></html>";

        return crow::response(os.str());
        });
	//alterar inscrição por índice
    CROW_ROUTE(app, "/alterar/inscricao/<int>")([](const crow::request& req, int index) {
        std::ostringstream os;
        if (index < 0 || index >= inscricoes.size()) {
            os << "<html><head><title>Alterar Inscrição</title></head><body>";
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>Inscrição não encontrada!</h1><button id='voltar'><a href='/alterar/inscricao'>Voltar</a></button></div></section>";
            os << "</body></html>";
            return crow::response(os.str());
		}
		os << "<html>";
		os << "<head><title>Alterar Inscrição</title>";
		os << "<link rel='stylesheet' href='/static/style.css'></head>";
		os << "<body>";
		os << "<section id='ms'>";
		os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Selecione uma nova atividade</h1>";

		const Inscricao& i = inscricoes[index];
        int indice = 0;
		bool atividadeEncontrada = false;
		os << "<div id='listagem'>";
        for (const auto& a : atividades) {
            if (indice != i.idAtividade) {
                os << "<div class='cardparticipante'>";
                os << "<h1>" << a.nomeAtividade << "</h1>";
                os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
                os << "<hr>";
                os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div><br></div>";
                os << "<div class='cardactions'><button style='width:6vw;'><a href='/alterar/inscricao/" << index << "/" << indice << "' style='color: green; '>Selecionar</a></button></div>";
                os << "</div>";
                atividadeEncontrada = true;
            }
            indice++;
			
        }
        if (!atividadeEncontrada) {
            os << "<h1 id='erro'>Nenhuma atividade disponível para alteração!</h1>";
		}
		os << "</div>"; 
		os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
		os << "<button id='voltar'><a href='/alterar/inscricao'>Voltar</a></button>";
		os << "</section></body></html>";
        return crow::response(os.str());
        });
	//alterar inscrição por índice e atividade
    CROW_ROUTE(app, "/alterar/inscricao/<int>/<int>").methods("GET"_method, "POST"_method)
        ([](const crow::request& req, int indexInscricao, int indexAtividade) {
        std::ostringstream os;
        Inscricao& i = inscricoes[indexInscricao];
        Participante& p = participantes[i.idParticipante];
        Atividade& a = atividades[indexAtividade];
        os << "<html>";
        os << "<head><title>inscricao</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";
        if (req.method == crow::HTTPMethod::GET) {
            os << "<section id='ms'>";
            os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Deseja inscrever?</h1>";
            os << "<div id='listagem'>";
            os << "<div class='cardparticipante'>";
            os << "<h1>" << p.nome << "</h1>";
            os << "<h5>Matrícula: " << p.matricula << " | " << p.idade << " anos</h5>";
            os << "<hr>";
            os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << "° período</p></div></div>";
            os << "</div>";
            os << "<h1 id='menutitle'>EM</h1>";
            os << "<div class='cardparticipante'>";
            os << "<h1>" << a.nomeAtividade << "</h1>";
            os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " - " << a.hora << " </h5>";
            os << "<hr>";
            os << "<div class='infosparticipante'><div><p>" << a.tipoAtividade << "</p><p>" << a.local << "</p></div></div>";
            os << "</div>";
            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;'>";
            os << "<form action='/alterar/inscricao/" << indexInscricao << "/" << indexAtividade << "' method='POST' style='display: flex; gap:2vw;'>";
            os << "<button id='voltar'><a href='/inscricao/participante/" << indexInscricao << "'>Cancelar</a></button>";
            os << "<button type='submit' value='inscrever' style='cursor: pointer;'><a>Inscrever</a></button>";
            os << "</form>";
            os << "</div>";
            os << "</section>";
            os << "</body>";
            os << "</html>";
            return crow::response(os.str());
        }
        else {
            
            Inscricao& i = inscricoes[indexInscricao];
			Participante& p = participantes[i.idParticipante];
            
            Atividade& antiga = atividades[i.idAtividade];
            Atividade& nova = atividades[indexAtividade];
			antiga.vagasDisponiveis++;
			nova.vagasDisponiveis--;
            i.participanteAtividade = nova.nomeAtividade;
            i.idAtividade = indexAtividade;
            if (a.esportiva) {
                p.participaEsporte = true;
                p.idAtvEsp = indexAtividade;
            };
            os << "<section id='ms'>\n"
				<< "<h1 id='menutitle' style='margin-bottom: 2vh;'>Inscrição alterada com sucesso!</h1>\n"
                << "<div id='listagem'>\n"
                << "<div class='cardparticipante'>\n"
                << "<h1>" << p.nome << "</h1>\n"
                << "<hr>\n"
                << "<div class='infosparticipante'><div><p>Atividade: " << nova.nomeAtividade << "</p></div><br></div>\n"
                << "</div>\n"
                << "</div>\n"
                << "<div id='menu' style='margin-top: 3vh;width: 12vw; height: 5.5vh;'>\n"
                << "<button id='voltar'><a href='/alterar/inscricao'>< Voltar</a></button>\n"
                << "</div>\n"
                << "</section>\n";
            return crow::response(os.str());
        }

            });
	//deletar inscrição
    CROW_ROUTE(app, "/inscricao/deletar/<int>").methods("GET"_method, "POST"_method)
        ([](const crow::request& req, int indiceVetor) {
        std::ostringstream os;

        int tamanho = inscricoes.size();
        if (indiceVetor < 0 || indiceVetor >= tamanho) {
            os << "<html>";
            os << "<head><title>Deletar inscrição</title>";
            os << "<link rel='stylesheet' href='/static/style.css'></head>";
            os << "<body>";
            os << "<section id='ms'>";
            os << "<div id='menu'>";
            os << "<h1 id='erro'>Inscrição não encontrada</h1>";
            os << "<button id=\"voltar\"><a href='/alterar/inscricao'>Voltar</a></button>";
            os << "</div>";
            os << "</section>";
            os << "</body></html>";
            return crow::response(os.str());
        }
        else {
            if (req.method == crow::HTTPMethod::GET) {
                const Participante& p = participantes[indiceVetor];
                std::ostringstream os;
                os << "<html>\n"
                    << "<head><link rel=\"stylesheet\" href=\"/static/style.css\">\n"
                    << "<title>Deletar inscrição</title>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<section id=\"ms\">\n"
                    << "<div id=\"containerform\">\n"
                    << "<h1 id=\"menutitle\">Deletar Inscrição</h1>\n"
                    << "<p>Tem certeza que deseja deletar essa inscrição?</p>\n"
                    << "<form action=\"/inscricao/deletar/" << indiceVetor << "\" method=\"POST\">\n"
                    << "<div id=\"botoes\">\n"
                    << "<button id=\"voltar\"><a href=\"/alterar/inscricao\">< Voltar</a></button>\n"
                    << "<button type=\"submit\" value=\"deletar\" style=\"cursor: pointer;\"><a>Deletar</a></button>\n"
                    << "</div>\n"
                    << "</form>\n"
                    << "</div>\n"
                    << "</section>\n"
                    << "</body>\n"
                    << "</html>\n";
                return crow::response(os.str());
            }
            else {
                Inscricao& i = inscricoes[indiceVetor];
                Atividade& a = atividades[i.idAtividade];
				a.vagasDisponiveis++;
                inscricoes.erase(inscricoes.begin() + indiceVetor);
                os << "<html>\n"
                    << "<head><title>Inscrição deletada Deletado</title>\n"
                    << "<link rel='stylesheet' href='/static/style.css'>\n"
                    << "</head>\n"
                    << "<body>\n"
                    << "<section id='ms'>\n"

                    << "<div id='listagem'>\n"
                    << "<h1 id='menutitle'>Inscrição Deletada com Sucesso</h1>\n"
                    << "</div>\n"
                    << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'><button id='voltar'><a href='/alterar/inscricao'>< Voltar</a></button></div>\n"
                    << "</section>\n"
                    << "</body>\n"
                    << "</html>\n";
                return crow::response(os.str());
            }
        }
            });
	//visualizar inscrições por data
    CROW_ROUTE(app, "/inscricao/visualizar/pordata")([]() {
        std::ostringstream os;
        os << "<html>\n"
            << "<head>\n"
            << "<title>Listagem</title>\n"
            << "<link rel='stylesheet' href='/static/style.css'>\n"
            << "</head>\n"
            << "<body>\n"
            << "<section id='ms'>\n"
            << "<div id='containerform'>\n"
            << "<h1 id='menutitle'>Listar por data</h1>\n"
            << "<form action='/inscricao/visualizar/pordata/get' method='GET'>\n"
            << "<div id='mid'>\n"
            << "<label for='inserirdata'>\n"
            << "<input type='date' name='data' id='inserirdata' required style='margin-left:1vw;'>\n"
            << "</label>\n"
            << "<button type='submit' style='margin-left:1vw;'>Listar</button>\n"
            << "</div>\n"
            << "</form>\n"
            << "</div>\n"
            << "<div id='menu' style='margin-top:3vh;'>\n"
            << "<button id='voltar'><a href='/'>< Voltar</a></button>\n"
            << "</div>\n"
            << "</section>\n"
            << "</body>\n"
            << "</html>\n";
        return crow::response(os.str());
        });
	//visualizar inscrições por data com GET
    CROW_ROUTE(app, "/inscricao/visualizar/pordata/get").methods("GET"_method)
        ([](const crow::request& req) {
        std::ostringstream os;
        std::string data = req.url_params.get("data") ? req.url_params.get("data") : "";

		data = formatarData(data); 

        os << "<html><head><title>Inscrições por Data</title>"
            << "<link rel='stylesheet' href='/static/style.css'>"
            << "</head><body>";
        os << "<section id='ms'>";

        if (data.empty()) {
            os << "<h1 id='menutitle'>Erro</h1>";
            os << "<p id='erro'>Data não informada.</p>";
        }
        else {
            os << "<h1 id='menutitle'>Inscrições na data: " << data << "</h1>";
            bool encontrou = false;
            os << "<div id='listagem'>";
            for (const auto& inscricao : inscricoes) {
                if (inscricao.dataInscricao == data) {
                    encontrou = true;
                    os << "<div class='cardparticipante'>";
                    os << "<h1>" << inscricao.participanteNome << "</h1>";
                    os << "<h5>Atividade: " << inscricao.participanteAtividade << "</h5>";
                    os << "<p>Data da inscrição: " << inscricao.dataInscricao << "</p>";
                    os << "</div>";
                }
            }

            if (!encontrou) {
                os << "<p id='erro'>Nenhuma inscrição encontrada para a data informada.</p>";
            }
        }
        os << "</div>";
        os << "<div id='menu' style='margin-top:3vh;'><button id='voltar'><a href='/inscricao/visualizar/pordata'>&lt; Voltar</a></button></div>";
        os << "</div></section></body></html>";

        crow::response res(os.str());
        res.set_header("Content-Type", "text/html");
        return res;
            });

    

    //css páginas
    CROW_ROUTE(app, "/static/style.css")([]() {
        crow::response res(R"(
            *,body,html {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
    font-family: Tahoma, sans-serif
}
#ms {
    width: 100vw;    
    min-height: 100vh;
    height: fit-content;
    display: flex;
    justify-content: center;
    align-items: center;
    flex-direction: column;
    background: linear-gradient(360deg,#5d5d5d,#303030,#000000);
    background-size: 180% 180%;
    animation: gradient-animation 15s ease infinite;            
}
#menu {
    width: fit-content;
    height: fit-content;
    display: flex;
    flex-direction: column; 
    justify-content: center;
    align-items: center;
    gap:3vh;
    padding: 4vh 5vw;
    background-color: rgb(119, 119, 119, 0.4);
    box-shadow: rgba(0, 0, 0, 0.1) 0px 2px 5px 1px;
    border-radius: 1vw;
}
#listagem {
  width: fit-content;
  max-width: 92vw;
  height: fit-content;
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  align-items: center;
  gap:3vh;
  padding: 2vh 1vw;
  background-color: rgb(119, 119, 119, 0.4);
  border-radius: 1vw;
  box-shadow: 0px 2px 5px 1px rgba(0, 0, 0, 0.1);
}
#containerform {
  width: fit-content;
    height: fit-content;
    display: flex;
    flex-direction: column; 
    justify-content: center;
    align-items: center;
    gap:3vh;
    padding: 2vh 3vw;
    background-color: rgb(119, 119, 119, 0.4);
    border-radius: 1vw;
    box-shadow: 0px 2px 5px 1px rgba(0, 0, 0, 0.1);
    
}
#menu button, #containerform button {
  width: 10vw;
  height: fit-content;
  text-align: center;
  
  font-size: 1.2vw;
  border-radius: 0.4vw;
  border: 0;
  transition: 100ms;
  box-shadow: 0px 2px 5px 1px rgba(0, 0, 0, 0.1);
}
#menu button a, #containerform button a {
  display: block;
  padding: 1vh 0;
  width: 100%;
  height: 100%;
  text-decoration: none;
  color: black;
  font-weight: 550;
}
#menutitle {
  font-size: 2vw;
  color: white;
  font-weight: bold;
  letter-spacing: 0.03  vw;
}
#menu:has(button:hover) button{
    opacity: 0.5;
}
#menu button:hover{
    opacity: 1 !important; 
}
hr {
  width: 100%;
}

label {
  width: fit-content;
  display: flex;
  flex-direction: column;
  color: white;
  
  font-weight: 600;
}
form {
  width: 100%;
  height: 100%;
}
#inputsdiv {
  width: fit-content;
  height: 100%;
  display: flex;
  gap: 2vw;
}
#mid {
  width: 100%;
  height: 100%;
  display: flex;
  flex-direction: column;
  gap: 1vh;
  align-items: center;
  justify-content: center ;
}
#direita,#esquerda {
  width: fit-content;
  height: 100%;
  display: flex;
  flex-direction: column;
  gap: 1vh;
}
#containerform input:not([type="radio"]), input:not([type="radio"]), select{
  width: 18vw;
  height: 3.5vh;
  border-radius: 0.35vw;
  padding-left: 0.3vw;
  font-size: 0.8vw;
  font-weight: 500;
  margin-top: 0.3vh;
  border: 0;
  box-shadow: 0px 2px 5px 1px rgba(0, 0, 0, 0.1);
}
input:not([type="radio"]):focus {
  outline: 0;
}
select:focus-visible {
  border-bottom-left-radius: 0;
  border-bottom-right-radius: 0;
  outline: 0;
}
option {
  border: 0;
  outline: 0;
}

option:last-child {
  border-bottom-left-radius: 0.35vw;
  border-bottom-right-radius: 0.35vw;
}
#botoes {
  width: 100%;
  height: fit-content;
  margin-top: 2vh;
  display: flex;
  justify-content: space-between;
  padding: 0, 10vw;
}
#voltar {
  background-color: transparent;
  border: 2px solid white !important;
  
}
#voltar a {
  color: white !important;
  font-weight: 300 !important;
  font-size: 1vw;
}
#divradio {
  width: 100%;
  height: 5vh;
  display: flex;
  gap: 0.5vw;
  
}
#divradio div {
  display: flex;
  align-items: center;
}
#divradio div input[type="radio"] {
  width: 1.5vw;
  height: 2vh;

}
.cardparticipante {
  width: 20vw;
  height: fit-content;
  border-radius: 0.5vw;
  padding: 1vw;
  background-color: rgb(238, 237, 237, 0.4);
  box-shadow: rgba(0, 0, 0, 0.1) 0px 2px 5px 1px;
}
.cardparticipante h1 {
  color: white;
  width: 100%;
}
.cardparticipante h5 {
  color: white;
  width: 100%;
  margin-bottom: 1vh;
}
.infosparticipante {
  width: 100%;
  margin-top: 1vh;
}
.infosparticipante div {
  width: 100%;
  display: flex;
  justify-content: space-between;
}
.infosparticipante p {
  font-size: 0.85vw;
  font-weight: 600;
}
.infosparticipante div p {
  width: fit-content;
  font-size: 0.85vw;
  font-weight: 600;
}
.cardactions {
  width: 100%;
  margin-top: 2vh;
  display: flex;
  gap: 1vw;
  justify-content: flex-end;
}
.cardactions button{
  width: 5vw;
  height: fit-content;
  text-align: center;
  border-radius: 0.4vw;
  border: 0;
  transition: 100ms;
  background-color: rgb(119, 119, 119, 0.95);
  box-shadow: 0px 2px 5px 1px rgba(0, 0, 0, 0.1);
}

.cardactions button a {
  display: block;
  font-weight: 1000;
  font-size: 1vw;
  cursor: pointer;
}
#searchbar {
  width: 23vw;
  padding: 0.7vh 0.5vw;
  background-color: rgb(119, 119, 119, 0.4);
  border-radius: 0.5vw;
  margin-bottom: 2vh;
  box-shadow: 0px 2px 5px 1px rgba(0, 0, 0, 0.1);
}
#searchbar input {
  width: 100%;
  height: 3.5vh;
}
#erro {
  font-size: 2vw;
  color: white;
}

@keyframes gradient-animation {
  0% {
    background-position: 0% 50%;
  }
  50% {
    background-position: 100% 50%;
  }
  100% {
    background-position: 0% 50%;
  }
}
        )");
        res.set_header("Content-Type", "text/css");
        return res;
        });
    app.port(18080).multithreaded().run();
};

