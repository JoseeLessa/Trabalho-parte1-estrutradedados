#  Gerenciador de Campeonato em C

Este projeto é uma aplicação de **console em C**, criada para **gerenciar e exibir estatísticas de um campeonato de futebol**.  
O sistema é capaz de ler dados de times e resultados de partidas, processar essas informações e apresentar um **placar de classificação**, além de permitir **consultas detalhadas**.


---

##  Visão Geral dos Recursos

- **Carregamento de Dados:** Lê e interpreta automaticamente os arquivos de times e partidas ao iniciar.  
- **Cálculo de Estatísticas:** Processa os resultados de todas as partidas para calcular em tempo real a pontuação, saldo de gols e V/E/D de cada time.  
- **Interface Interativa:** Um menu de console simples e direto para acessar todas as funcionalidades.  
- **Consulta de Times:** Permite buscar times por prefixo (sem diferenciar maiúsculas/minúsculas) e exibe suas estatísticas completas.  
- **Consulta de Partidas:** Lista todos os jogos em que um time (buscado por prefixo) participou.  
- **Tabela de Classificação:** Exibe uma tabela completa e formatada com o desempenho de todos os times no campeonato.

---

##  Arquitetura do Código

O projeto é estruturado de forma **modular**, separando a lógica principal, a interface e as funções utilitárias.

###  Arquivos Principais

#### `main.c`
**Propósito:** Ponto de entrada da aplicação.  
**Responsabilidades:**  
- Aloca a memória principal para os "bancos de dados" (`BDTeams`, `BDPartidas`).  
- Gerencia o menu interativo (loop principal).  
- Direciona o fluxo do usuário para as funções apropriadas.

#### `campeonato.h`
**Propósito:** O “contrato” do sistema.  
**Responsabilidades:**  
- Define as estruturas de dados centrais (`Team`, `Partida`, `BDTeams`, `BDPartidas`).  
- Declara os protótipos de todas as funções públicas implementadas em `campeonato.c`.

#### `campeonato.c`
**Propósito:** O “core” da aplicação.  
**Responsabilidades:**  
- Implementa toda a **lógica de negócio**.  
- Carrega arquivos, calcula pontos, processa buscas e formata a tabela de classificação.

#### `utils.h`
**Propósito:** Caixa de ferramentas de utilitários.  
**Responsabilidades:**  
- Fornece funções `inline` otimizadas e seguras para manipulação de strings, como:  
  - `str_trim` — remove espaços.  
  - `safe_atoi` — conversão segura de string para `int`.  
  - `str_starts_with_case_insensitive` — comparação de prefixos ignorando maiúsculas/minúsculas.

#### `Makefile`
**Propósito:** Automação de build.  
**Responsabilidades:**  
- Compila todos os arquivos `.c` em objetos `.o` e vincula no executável final `campeonato_gronerjose`.  
- Inclui alvos para **compilar**, **executar** e **limpar** o projeto.

---

## 🛠️ Como Compilar e Executar

### 1. Requisitos
- Compilador **gcc**  
- Utilitário **make**

### 2. Compilação
No terminal, execute:
```bash
make
```
Isso criará o arquivo executável **`campeonato_gronerjose`**.

### 3. Execução

#### Método A — Via Makefile
Compila (se necessário) e executa o programa automaticamente:
```bash
make run
```

#### Método B — Manualmente
Execute o binário diretamente:
```bash
./campeonato_gronerjose
```

---

## 💡 Arquivos de Dados

O programa espera encontrar os seguintes arquivos **no mesmo diretório do executável**:

- `times.csv`
- `partidas_parcial.csv`

> ⚠️ Os nomes e caminhos desses arquivos estão definidos em `main.c`.  
> Caso deseje usar outros nomes, altere as variáveis `teams_path` e `matches_path` antes de compilar.

---

## 🧠 Conceitos Técnicos Aplicados

- **Modularidade:**  
  A lógica é separada da interface.  
  `main.c` lida com o *“o quê”* (menu), enquanto `campeonato.c` lida com o *“como”* (lógica).

- **Tipos Abstratos de Dados (TADs):**  
  Estruturas como `Team` e `Partida` encapsulam os dados, e funções como `team_points` e `team_add_match` operam sobre elas.

- **Gerenciamento de Memória:**  
  Uso de `malloc` em `main.c` para alocar dinamicamente as estruturas principais, passadas por ponteiros entre módulos.

- **Manipulação de Arquivos:**  
  Uso de `fopen`, `fgets` e `sscanf` em `campeonato.c` para ler e interpretar arquivos `.csv` linha a linha.

- **Funções Utilitárias:**  
  O arquivo `utils.h` demonstra o uso de funções `static inline` para otimizar operações comuns sem necessidade de um `.c` separado.

---

##  Evolução do Projeto (Próximos Passos)

- [ ] **Implementar Ordenação:**  
  A tabela de classificação (opção 6) atualmente exibe os times por ID.  
  O próximo passo é ordená-la por **Pontos (PG)**, **Saldo de Gols (S)** e **Gols Marcados (GM)**.

- [ ] **Completar o Menu:**  
  Implementar as opções de menu ausentes (como 3, 4, 5) para **adicionar, editar ou remover times e partidas**.

- [ ] **Parâmetros de Linha de Comando:**  
  Modificar `main.c` para aceitar os nomes dos arquivos de times e partidas como argumentos de linha de comando:
  ```bash
  ./campeonato_gronerjose times.csv partidas.csv
  ```




---

📍 **Autor:** *José e Pedro Groner*  


