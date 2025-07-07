

# 📦 Inicialização e Execução do Projeto

Este guia descreve o passo a passo necessário para clonar, compilar e executar o projeto localmente em um ambiente Windows.

## 🚀 Etapas de Execução

### 1️⃣ Clonar o repositório

Abra o terminal (CMD, PowerShell ou Git Bash) e execute:

```bash
git clone https://github.com/Madusalves/GerenciadorUniversitario.git
```


---

### 2️⃣ Executar o script `.bat` de configuração

Navegue até a pasta do projeto e execute o script `.bat`:

```bash
cd GerenciadorUniversitario
.\buildarProjeto.bat
```

> O script pode instalar dependências ou configurar variáveis de ambiente, dependendo da sua implementação.

---

### 3️⃣ Acessar o diretório de build

Após a execução do script, entre na pasta `build` gerada:

```bash
cd build
```

---

### 4️⃣ Compilar o projeto com CMake

Execute o comando para compilar o projeto:

```bash
cmake --build .
```

Esse comando utilizará os arquivos de configuração CMake para compilar o projeto de acordo com o compilador e build system configurado.

---

## 🧪 Execução da aplicação

Após a compilação, o executável estará disponível na pasta `build`. Basta rodá-lo diretamente:

```bash
./meu_crow_app.exe
```

> Substitua `NomeDoExecutavel.exe` pelo nome real gerado pela compilação.

---

## ❓ Suporte

Se você encontrar qualquer problema durante a configuração ou execução do projeto, abra uma [issue](https://github.com/seu-usuario/seu-repositorio/issues) ou entre em contato diretamente.

---

<br>





# - Trabalho Acadêmico em C++

Este projeto foi desenvolvido como parte de um trabalho acadêmico em C++, com o objetivo de praticar a manipulação de entradas e saídas de dados, uso de estruturas condicionais, laços de repetição, vetores, funções e outros recursos fundamentais da linguagem.
