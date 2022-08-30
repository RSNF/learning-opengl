# Learning OpenGL

O [OpenGL](https://www.opengl.org) é uma API livre utilizada na computação gráfica, para desenvolvimento de aplicativos gráficos, ambientes 3D, jogos, entre outros.

É possível utilizá-la em diversas IDEs, como o [Dev-C++](https://www.bloodshed.net) e o [Code::Blocks](https://www.codeblocks.org), mas vamos entender como fazer isso pelo [Visual Studio Code](https://code.visualstudio.com).

***Vamos lá!*** :smile:

#### 1° passo - Instalação do MSYS2:

* Essa ferramenta vai ser útil para instalar os pacotes necessários para rodar os projetos com OpenGL.

* Link para download: [MSYS2](https://www.msys2.org)

#### 2° passo - Download do compilador:

* Compilador de C/C++:
```bash
  pacman -S mingw-w64-x86_64-gcc
```

Após finalizado, é necessário adicionar ao `Path` das variáveis de ambiente do sistema, o caminho da pasta *bin* do diretório de instalação do MinGW. Ele vai estar dentro da pasta de instalação do MSYS, **caso não tenha alterado** o diretório de instalação será o seguinte:

```bash
  C:\msys64\mingw64\bin
```

Para confirmar se a instalação foi bem sucedida, abra o CMD e utilize os comandos `gcc --version` e `g++ --version`, caso não funcione, reinicie o computador e tente novamente.

#### 3° passo - Download dos pacotes do OpenGL:

```bash
  pacman -S mingw-w64-x86_64-freeglut
```

```bash
  pacman -S mingw-w64-x86_64-glew
```

#### 4° passo - Execução do projeto:

* Faça o download do arquivo `casa.cpp` disponível neste repositório.
* Abra o CMD na mesma pasta de download do arquivo e execute o seguinte comando:
```bash
  g++ casa.cpp -o casa -lopengl32 -lfreeglut -lglu32 -lwinmm -lgdi32
```
Se tudo correr bem, será gerado um arquivo .exe e você poderá abri-lo para ver a casa.
