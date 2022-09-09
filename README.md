# Learning OpenGL

O [OpenGL](https://www.opengl.org) é uma API livre utilizada na computação gráfica, para desenvolvimento de aplicativos gráficos, ambientes 3D, jogos, entre outros.

É possível utilizá-la em diversas IDEs, como o [Dev-C++](https://www.bloodshed.net) e o [Code::Blocks](https://www.codeblocks.org), mas vamos entender como fazer isso pelo [Visual Studio Code](https://code.visualstudio.com).

***Vamos lá!*** :smile:

#### 1° passo - Instalação do MSYS2:

* Essa ferramenta vai ser útil para instalar os pacotes necessários para rodar os projetos com OpenGL.

* [Clique aqui](https://www.msys2.org) para efetuar o download da ferramenta.

* Ao final da instalação será aberta uma janela com um terminal, que é onde vamos digitar os comandos para instalação dos pacotes.

#### 2° passo - Download do compilador e depurador:

* Copie o comando abaixo e cole no terminal do MSYS2 para instalar o `compilador` de C/C++:

```bash
pacman -S mingw-w64-x86_64-gcc
```

Após finalizado, é necessário adicionar ao `Path` das variáveis de ambiente do sistema, o caminho da pasta *bin* do diretório de instalação do MinGW. Ele vai estar dentro da pasta de instalação do MSYS2. **Caso você não tenha alterado**, o diretório de instalação será o seguinte:

```bash
C:\msys64\mingw64\bin
```

***Clicando neste [link](https://satellasoft.com/artigo/windows/windows-10-como-alterar-as-variaveis-de-ambiente) você pode ver como fazer essa alteração nas variáveis de ambiente.***

Para confirmar se a instalação foi bem sucedida, abra o CMD e execute o comando `g++ --version`. Caso não retorne um resultado válido, reinicie o computador e tente executá-lo novamente.

* Copie o comando abaixo e cole no terminal do MSYS2 para instalar o `depurador`, ele vai facilitar nossa vida no VS Code (essa instalação é *opcional*, o **depurador** só será útil no **passo 6**):

```bash
pacman -S mingw-w64-x86_64-gdb
```

Assim como o gcc, para confirmar se a instalação correu bem, você pode executar o comando `gdb --version` no CMD.

#### 3° passo - Download dos pacotes do OpenGL:

* Também no terminal do MSYS2, executaremos os comandos abaixo para instalação dos pacotes, esses vão demorar menos que o gcc, já que são menores.

```bash
pacman -S mingw-w64-x86_64-freeglut
```

```bash
pacman -S mingw-w64-x86_64-glew
```

*Caso o projeto que você for executar exija outros pacotes, como o GLFW e SDL2, você pode pesquisar no próprio site do [MSYS2](https://packages.msys2.org/package/) que vai encontrar as informações sobre eles e como instalá-los.*

#### 4° passo - Instalação e configuração do ambiente (Visual Studio Code)

* [Clique aqui](https://code.visualstudio.com) para efetuar o download da IDE.

* Finalizada a instalação, vá até a aba de extensões, procure e instale a seguinte: `ms-vscode.cpptools`.

* Faça o download do arquivo `casa.cpp` disponível neste repositório, na pasta de **exemplos**.

* Salve esse arquivo numa nova pasta e abra essa pasta no VS Code.

#### 5° passo - Execução do projeto:

* Abra um novo terminal, dentro do VS Code, e execute o seguinte comando:
```bash
g++ casa.cpp -o casa -lopengl32 -lfreeglut -lglu32 -lwinmm -lgdi32
```
Se tudo correr bem, será gerado um arquivo **.exe**, para abrí-lo basta chamar o próprio executável pelo terminal, digitando: `./casa.exe` :house:.

Com isso, já dá pra executar os projetos, mas pra evitar ter que ficar inserindo esses comandos via terminal toda vez, vamos dar uma "embelezada" no negócio...

#### 6° passo - *Opcional*:

:warning: **Para os passos a seguir, mantenha o arquivo `casa.cpp` sempre aberto ao selecionar as opções do menu da IDE.**

* Preparação do build do código:
  - Acesse o menu **Terminal > Configurar Tarefa de Build Padrão**.
  - Selecione a opção do **g++**.
  - Será criado um arquivo `tasks.json` na pasta **.vscode**.
  - Dentro do parâmetro ***args***, vamos acrescentar o seguinte:

```bash
"-lopengl32", "-lfreeglut", "-lglu32", "-lwinmm", "-lgdi32"
```

Através do atalho **Ctrl + Shift + B** ou por meio do menu **Terminal > Executar Tarefa de Build**, podemos gerar o arquivo **.exe** que vimos anteriormente (*lembrando que o arquivo **casa.cpp** deve estar aberto*). Isso já poupa um dos comandos que a gente estava usando no terminal, vamos para o próximo.

* Execução do arquivo de build:
  - Acesse o menu **Executar > Adicionar Configuração**.
  - Selecione a opção **C++ (GDB/LLDB)**.
  - Será gerado um arquivo `launch.json` na pasta **.vscode**.
  - Caso o arquivo gerado esteja com o parâmetro *configurations* vazio, você pode copiar o que está nesse repositório, ou seguir o passo descrito logo abaixo.
  
*Uma outra forma de gerar esse arquivo é clicando no ícone da engrenagem (**Adicionar a configuração de depuração**), que está no canto superior direito da janela da aplicação, e selecionar a opção com o **g++***.

Com o arquivo criado, nos atentaremos aos seguintes parâmetros: `program`, `miDebuggerPath` e `preLaunchTask`.

`program`: vamos informar onde está o arquivo **.exe**, caso você tenha alterado o nome, é importante informar corretamente aqui. Normalmente mantemos o mesmo caminho da pasta principal, inserindo o seguinte: **"${workspaceFolder}/casa.exe"**.

Esse caminho deve ser o mesmo informado no *args* do arquivo *tasks.json*, que deve aparecer algo como: **"\${workspaceFolder}/${fileBasenameNoExtension}.exe"**, indicando onde será gerado o arquivo **.exe**.

`miDebuggerPath`: vamos informar onde se encontra o depurador '**gdb.exe**' que instalamos no **passo 2**, ele vai estar dentro da pasta *bin* do MinGW, mas caso você tenha alterado o diretório de instalação, se atente a isso.

`preLaunchTask`: vamos informar qual o nome (identificador) da tarefa de build que fizemos anteriormente, para isso vamos até o arquivo **tasks.json** e verificar o parâmetro **label**, é obrigatório que esses dois parâmetros tenham o mesmo valor nos dois arquivos, pode ser o nome que quiser, contanto que sejam iguais.

* Configuração do compilador:
  - Salve todas as alterações nos arquivos de **launch.json** e **tasks.json**.
  - Pressione **Ctrl + Shift + P** e pesquise por `C/C++: Editar Configurações(IU)`.
  - Altere o **Caminho do compilador** para aquele que informar o **g++**.
  - Caso tenha algum problema com o **Modo do IntelliSense**, altere para **windows-gcc-x64**.
  
Feito isso, agora é só alegria! :smile:

Mantenha o arquivo `casa.cpp` aberto e pressione **`F5`**. Pronto, sucesso! :rocket:

### :mag_right: Referências

* [Get Started with C++ and Mingw-w64 in Visual Studio Code](https://code.visualstudio.com/docs/cpp/config-mingw).

* [Configurando minGW e SDL2 no Visual Studio Code](https://medium.com/estado-pensante/configurando-mingw-e-sdl2-no-visual-studio-code-5c1ae2f5a1c6).

* [Configurando o OpenGl no Dev C++](http://www.univasf.edu.br/~jorge.cavalcanti/configdev.html).
