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


struct Atividade {
    string nomeAtividade;
    string tipoAtividade;
    string local;
    string data;
    string hora;
    int vagasDisponiveis;
};
vector<Atividade> atividades;

struct Incricao {
    string participanteNome;
    string participanteAtividade;
    string dataInscricao;
    string presencaConfirmada;
};

vector<Incricao> inscricoes;
int main() {
    crow::SimpleApp app;
    //main
    CROW_ROUTE(app, "/")([]() {
        return R"(
            <html>
            <head>
                <title>Gerenciamento universit�rio</title>
                <link rel="stylesheet" href="/static/style.css">
            </head>
            <body>
                <section id='ms'>
                    <div id='menu'>
                        <h1 id="menutitle">Menu</h1>
                        <button><a href="/cadastro">Cadastrar</a></button>
                        <button><a href="/alterar">Alterar</a></button>
                        <button><a href="/inscrever">Inscrever</a></button>
                    </div>
                </section>
             </body>
            </html>
        )";
        });
    //menu de cadastros
    CROW_ROUTE(app, "/cadastro")([]() {
        return R"(
            <html>
                <head>
                    <link rel="stylesheet" href="/static/style.css">
                    <title>Cadastro</title>
                </head>
                <body>
                    <section id="ms">
                        <div id="menu">    
                            <h1 id="menutitle">Cadastrar</h1>
                            <button><a href="/cadastro/participante">Participante</a></button>
                            <button><a href="/cadastro/atividade">Atividade</a></button>
                            <hr>
                            <button id="voltar"><a href="/">< Voltar</a></button>
                        </div>
                    </section>
                </body>
            </html>
        )";
    });
	//menu de altera��es
    CROW_ROUTE(app, "/alterar")([]() {
        return R"(
            <html>
                <head>
                    <title>Alterar</title>
                    <link rel="stylesheet" href="/static/style.css">
                    <title>Alterar</title>
                </head>
                <body>
                    <section id="ms">
                    <div id="menu">    
                        <h1 id="menutitle">Alterar</h1>
                        <button><a href="/alterar/participante">Participante</a></button>
                        <button><a href="/alterar/atividade">Atividade</a></button>
                        <hr>
                        <button id="voltar"><a href="/">< Voltar</a></button>
                    </div>
                    </section>
                </body>
            </html>
        )";
        });
    //cadastro participante
    CROW_ROUTE(app, "/cadastro/participante")([]() {
        return R"(
            <html>
            <head><link rel="stylesheet" href="/static/style.css">
            <title>cadastro paciente</title>
            </head>
            <body>   
                <section id="ms">
                    <div id="containerform">
                        <h1 id="menutitle">Cadastro de participante</h1>    
                        <form action="/cadastro/participante" method="POST">
                            <div id="inputsdiv">
                                <div id="esquerda">
                                    <label>Nome: <input type="text" name="nome" required placeholder="Nome completo"></label>
                                    <label>Matr�cula: <input type="text" name="matricula" required></label>
                                    <label>Curso: <input type="text" name="curso" required></label>
                                    <label>Semestre: <input type="number" name="semestre" required></label>
                                    <label>E-mail: <input type="email" name="email" placeholder="email@gmail.com" required></label>
                                </div>
                                <div id="direita">
                                    <label>Celular: <input type="text" name="celular" placeholder="(99) 99999-9999" required></label>
                                    <label>G�nero: <input type="text" name="genero" required></label>
                                    <label>Idade: <input type="number" name="idade" required></label>
                                    <label>Tipo: <input type="text" name="tipoParticipante" required></label>
                                    <label>
                                        Esportivo: 
                                            <div id="divradio">
                                                <div><input type="radio" name="esportivo" value='sim' required>Sim</div>
                                
                                                <div><input type="radio" name="esportivo" value='nao' required>N�o</div>
                                            </div>
                                    </label>
                                </div>
                            </div>
                            <div id="botoes">
                                <button id="voltar"><a href="/cadastro">< Voltar</a></button>
                                <button type="submit" value="Cadastrar" style="cursor: pointer;"><a>Cadastrar</a></button>
                            </div>
                        </form>
                </div>
            </section>
        </body>
        </html>
        )";
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
        p.participaDeAtividadesEsportivas = qs.get("esportivo") && string(qs.get("esportivo")) == "nao";

        participantes.push_back(p);
        std::ostringstream os;
        os << "<html><body>";
        os << "<h1>Participante Cadastrado com Sucesso</h1>";
        os << "<p><strong>Nome:</strong> " << p.nome << "</p>";
        os << "<p><strong>Matr�cula:</strong> " << p.matricula << "</p>";
        os << "<a href='/'>Voltar</a>";
        os << "</body></html>";

        return crow::response(os.str());
    });
    //colocar pattern na hora
    CROW_ROUTE(app, "/cadastro/atividade")([]() {
        return R"(
            <html>
            <head>    
                <link rel="stylesheet" href="/static/style.css">
                <title>cadastro atividade</title>
            </head>
            <body>
                <section id="ms">
                    <div id="containerform">
                        <h1 id="menutitle">Cadastro de atividade</h1>
                        <form action="/cadastro/atividade" method="POST">
                            <div id="mid">
                                <label style="width: 100% !important; ">Nome <input type="text" name="nome" style="width: 100% !important; "></label>
                                <label style="width: 100% !important; ">Tipo <input type="text" name="tipo" style="width: 100% !important; "></label>
                                <label style="width: 100% !important; ">Local <input type="text" name="local" style="width: 100% !important; "></label>
                                <label style="width: 100% !important; ">Data <input type="date" name="data" style="width: 100% !important; "></label>
                                <label style="width: 100% !important; ">Horario (HH:MM) <input type="text" name="hora" pattern="\d{2}:\d{2}" style="width: 100% !important; "></label>
                                <label style="width: 100% !important; ">Vagas disponiveis <input type="number" name="vagas" style="width: 100% !important; "></label>
                                <div id="botoes">
                                    <button id="voltar"><a href="/cadastro">< Voltar</a></button>
                                    <button type="submit" value="Cadastrar" style="cursor: pointer;"><a>Cadastrar</a></button>
                                </div>
                            </div>
                        </form>
                    </div>
                </section>
            </body>
            </html>
        )";
        });


    //processamento do cadastro de participante
    CROW_ROUTE(app, "/cadastro/atividade").methods("POST"_method)
        ([](const crow::request& req) {
        Atividade a;

        auto qs = req.get_body_params();
        a.nomeAtividade = qs.get("nome") ? qs.get("nome") : "";
        a.tipoAtividade = qs.get("tipo") ? qs.get("tipo") : "";
        a.local = qs.get("local") ? qs.get("local") : "";
        a.data = qs.get("data") ? qs.get("data") : "";
        a.hora = qs.get("hora") ? qs.get("hora") : "";
        a.vagasDisponiveis = qs.get("vagas") ? atoi(qs.get("vagas")) : 0;

        atividades.push_back(a);
        std::ostringstream os;
        os << "<html><body>";
        os << "<h1>Atividade cadastrada com sucesso</h1>";
        os << "<p><strong>Nome:</strong> " << a.nomeAtividade << "</p>";
        os << "<p><strong>Data:</strong> " << a.data << ' - ' << a.hora << "</p>";
        os << "<a href='/'>Voltar</a>"; 
        os << "</body></html>";

        return crow::response(os.str());
            });

    CROW_ROUTE(app, "/inscrever")([]() {
        return R"(
        <html>
        <head><title>Cadastro de Inscri��o</title></head>
        <body>
            <h1>Cadastro de Inscri��o</h1>
            <form action="/inscrever" method="POST">
                Nome do Participante: <input type="text" name="participanteNome" required><br><br>
                Atividade: <input type="text" name="participanteAtividade" required><br><br>
                Data da Inscri��o (DD/MM/AAAA): <input type="date" name="dataInscricao" pattern="\d{2}/\d{2}/\d{4}" required><br><br>
                Presen�a Confirmada? 
                <select name="presencaConfirmada" required>
                    <option value="sim">Sim</option>
                    <option value="n�o">N�o</option>
                </select><br><br>
                <input type="submit" value="Inscrever">
            </form>
            <br>
            <a href='/'>Voltar</a>
        </body>
        </html>
        )";
        });


    CROW_ROUTE(app, "/alterar/participante")([](const crow::request& req) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>Alterar participante</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";

        const char* pesquisa_param = req.url_params.get("pesquisa");

        if (participantes.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>N�o h� participantes cadastrados!</h1><button id='voltar'><a href='/alterar'>< Voltar</a></button></div></section>";
        }
        else {
            os << "<section id='ms'>";
            os << "<h1 id='menutitle' style='margin-bottom: 2vh;'>Alterar participante</h1>";
            os << "<div id='searchbar'>";
            os << "<form action='/alterar/participante' method='GET'>";
            
            int indice = 0;
            if (pesquisa_param) {
                
                std::string termo_pesquisa = pesquisa_param;
                
                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por matr�cula...' value='" << termo_pesquisa << "' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";

                
                bool found_match = false;
                
                for (const auto& p : participantes) {
                    if (p.matricula == termo_pesquisa) { 
                        os << "<div class='cardparticipante'>";
                        os << "<h1>" << p.nome << "</h1>";
                        os << "<h5>Matr�cula: " << p.matricula << " | " << p.idade << " anos</h5>";
                        os << "<hr>";
                        os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << " per�odo</p></div><br><p>Atividades esportivas?: " << p.participaDeAtividadesEsportivas << "</p></div>";
                        os << "<div class='cardactions'><button><a href='/participante/" << indice << "' style='color: yellow;'>Alterar</a></button><button><a href='/participante/deletar/" << indice << "' style='color: red;'>Excluir</a></button></div>";
                        os << "</div>";
                        found_match = true;
                    }
					indice++;
                }
                if (!found_match) {
                    os << "<p style='color: white; font-size:1.5vw;'>Nenhum participante encontrado com a matr�cula: " << termo_pesquisa << "</p>";
                }

            }
            else {
                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por matr�cula...' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";
                for (const auto& p : participantes) {
                    os << "<div class='cardparticipante'>";
                    os << "<h1>" << p.nome << "</h1>";
                    os << "<h5>Matr�cula: " << p.matricula << " | " << p.idade << " anos</h5>";
                    os << "<hr>";
                    os << "<div class='infosparticipante'><div><p>" << p.curso << "</p><p>" << p.semestre << " per�odo</p></div><br><p>Atividades esportivas?: " << (p.participaDeAtividadesEsportivas ? "N�o" : "Sim") << "</p></div>";
                    os << "<div class='cardactions'><button><a href='/participante/" << indice << "' style='color: yellow;'>Alterar</a></button><button><a href='/participante/deletar/" << indice << "' style='color: red;'>Excluir</a></button></div>";
                    os << "</div>";
                    indice++;
                }
            }
            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href=' /alterar'>< Voltar</a></button>";
        }

        os << "</body>";
        os << "</html>";
        return crow::response(os.str());
        });
        
    CROW_ROUTE(app, "/alterar/atividade")([](const crow::request& req) {
        std::ostringstream os;
        os << "<html>";
        os << "<head><title>Alterar atividade</title>";
        os << "<link rel='stylesheet' href='/static/style.css'></head>";
        os << "<body>";

        const char* pesquisa_param = req.url_params.get("pesquisa");

        if (atividades.empty()) {
            os << "<section id='ms'><div id= 'menu'><h1 id='erro'>N�o h� atividades cadastradas!</h1><button id='voltar'><a href='/alterar'>< Voltar</a></button></div></section>";
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
                        os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " </h5>";
                        os << "<hr>";
                        os << "<div class='infosparticipante'><div><p>" << a.local << "</p><p>" << a.hora << "</p></div><br></div>";
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
                os << "<input type='search' name='pesquisa' placeholder='Pesquisar por matr�cula...' required>";
                os << "</form>";
                os << "</div>";
                os << "<div id='listagem'>";
                for (const auto& a : atividades) {
                    os << "<div class='cardparticipante'>";
                    os << "<h1>" << a.nomeAtividade << "</h1>";
                    os << "<h5>Vagas: " << a.vagasDisponiveis << " | " << a.data << " </h5>";
                    os << "<hr>";
                    os << "<div class='infosparticipante'><div><p>" << a.local << "</p><p>" << a.hora << "</p></div><br></div>";
                    os << "<div class='cardactions'><button><a href='/atividade/" << indice << "' style='color: yellow;'>Alterar</a></button><button><a href='/atividade/deletar/" << indice << "' style='color: red;'>Excluir</a></button></div>";
                    os << "</div>";
                    indice++;
                }
            }
            os << "</div>";
            os << "<div id='menu' style = 'margin-top: 3vh;width: 12vw; height: 5.5vh;'>";
            os << "<button id='voltar'><a href=' /alterar'>< Voltar</a></button>";
        }

        os << "</body>";
        os << "</html>";
        return crow::response(os.str());
        });

    CROW_ROUTE(app, "/participante/<int>")
        ([](int indiceVetor) {
        std::ostringstream os;
		
		int tamanho = participantes.size();
        if (indiceVetor < 0 || indiceVetor >= tamanho) {
            os << "<html>";
            os << "<head><title>Alterar Participante</title>";
            os << "<link rel='stylesheet' href='/static/style.css'></head>";
            os << "<body>";
			os << "<section id='ms'>";
			os << "<div id='menu'>";
            os << "<h1 id='erro'>Participante n�o encontrado</h1>";
            os << "<button id=\"voltar\"><a href='/alterar/participante'>Voltar</a></button>";
			os << "</div>";
			os << "</section>";
            os << "</body></html>";
            return crow::response(os.str());
        }
        else {
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
                   << "<form action=\"/cadastro/participante\" method=\"POST\">\n"
                   << "<div id=\"inputsdiv\">\n"
                   << "<div id=\"esquerda\">\n"
                   << "<label>Nome: <input value=\"" << p.nome << "\" type=\"text\" name=\"nome\" required placeholder=\"Nome completo\"></label>\n"
                   << "<label>Matr�cula: <input value=\"" << p.matricula << "\" type=\"text\" name=\"matricula\" readonly required></label>\n"
                   << "<label>Curso: <input value=\"" << p.curso << "\" type=\"text\" name=\"curso\" required></label>\n"
                   << "<label>Semestre: <input value=\"" << p.semestre << "\" type=\"number\" name=\"semestre\" required></label>\n"
                   << "<label>E-mail: <input value=\"" << p.email << "\" type=\"email\" name=\"email\" placeholder=\"email@gmail.com\" required></label>\n"
                   << "</div>\n"
                   << "<div id=\"direita\">\n"
                   << "<label>Celular: <input value=\"" << p.celular << "\" type=\"text\" name=\"celular\" placeholder=\"(99) 99999-9999\" required></label>\n"
                   << "<label>G�nero: <input value=\"" << p.genero << "\" type=\"text\" name=\"genero\" required></label>\n"
                   << "<label>Idade: <input value=\"" << p.idade << "\" type=\"number\" name=\"idade\" required></label>\n"
                   << "<label>Tipo: <input value=\"" << p.tipoParticipante << "\" type=\"text\" name=\"tipoParticipante\" required></label>\n"
                   << "<label>Esportivo:\n"
                   << "<div id=\"divradio\">\n"
                   << "<div><input type=\"radio\" name=\"esportivo\" value='sim' " << (!p.participaDeAtividadesEsportivas ? "checked" : "") << " required>Sim</div>\n"
                   << "<div><input type=\"radio\" name=\"esportivo\" value='nao' " << (p.participaDeAtividadesEsportivas ? "checked" : "") << " required>N�o</div>\n"
                   << "</div>\n"
                   << "</label>\n"
                   << "</div>\n"
                   << "</div>\n"
                   << "<div id=\"botoes\">\n"
                   << "<button id=\"voltar\"><a href=\"/cadastro\">< Voltar</a></button>\n"
                   << "<button type=\"submit\" value=\"Cadastrar\" style=\"cursor: pointer;\"><a>Cadastrar</a></button>\n"
                   << "</div>\n"
                   << "</form>\n"
                   << "</div>\n"
                   << "</section>\n"
                   << "</body>\n"
                   << "</html>\n";
                return crow::response(os.str());
        }

        
            });
    //css p�ginas
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
            #containerform input:not([type="radio"]), input:not([type="radio"]){
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
        )"); // Define o tipo de conte�do como CSS
        res.set_header("Content-Type", "text/css");
        return res;
        });
    app.port(18080).multithreaded().run();
}