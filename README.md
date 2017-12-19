# SyncPi
Sistema de sincronização de vídeo em múltiplas telas com RaspberryPi 3 model B

Projeto de Graduação de curso de Ciência da Computação da Universidade Anhembi Morumbi

Elaborado por:
 - ANA CAROLINA DE BRANCO
 - FERNANDA LIVIERO FERNANDES POLO
 - LEANDRO FORCEMO DE OLIVEIRA
 - MARCOS ANTONIO LEITE ROCHA
 - RUBENS DIAS NETO

Sob a orientação do Professor Mestre Emerson Santos Paduan

------------------------------------------------------------------------------------------

O sistema foi desenvolvido utilizando o openFrameworks, um toolkit open source C++ distribuído sob a licença MIT com o addon ofxOMXPlayer.
 - http://openframeworks.cc/versions/v0.9.8/of_v0.9.8_linuxarmv6l_release.tar.gz

Foram feitas pequenas alterações no addon original, para a versão atualizada, utilizar o fork:
 - http://github.com/diasbinho/ofxOMXPlayer

É necessária a instalação dos arquivos de dependênicas do framework nos RPi player para rodar o SyncPi.
 - https://github.com/diasbinho/SyncPi/blob/master/install_codecs.sh
 - https://github.com/diasbinho/SyncPi/blob/master/install_dependencies.sh 
 
 ------------------------------------------------------------------------------------------
 
 <Strong>Configurando o RPi</Strong>

Para a instalação do Sistema operacional foi baixada a imagem do Raspian Jessie (http://downloads.raspberrypi.org/raspbian/images/raspbian-2017-07-05/) no site oficial. Para gravar a imagem no cartão de memória foi utilizado o Etcher (https://etcher.io/). Basta inserir o cartão de memória e o sistema é reconhecido. 

Para a versão instalada, no terminal de comando que mostra a versão do Raspian é:

	$ cat /etc/os-release

Se o sistema instalado estiver correto, deve aparecer a seguinte mensagem:

	PRETTY_NAME="Raspbian GNU/Linux 8 (jessie)"
	NAME="Raspbian GNU/Linux"
	VERSION_ID="8"
	VERSION="8 (jessie)"
	ID=raspbian
	ID_LIKE=debian
	HOME_URL="http://www.raspbian.org/"
	SUPPORT_URL="http://www.raspbian.org/RaspbianForums"
	BUG_REPORT_URL="http://www.raspbian.org/RaspbianBugs"

Para verificar a versão de Kernel e CPU é utilizado o seguinte comando no terminal: 

	$ uname -a

O retorno é a versão do Kernel, processador e data do sistema como no exemplo abaixo:

	Linux pi 4.9.35-v7+ #1014 SMP Fri Jun 30 14:47:43 BST 2017 armv7l GNU/Linux

Após a instalação, os dispositivos foram conectados na rede Wi-Fi através da interface gráfica Pixel, carregada no Boot padrão. Em seguida, foi necessário configurar os embarcados para iniciar sem a interface gráfica a fim de reduzir o consumo de memória, habilitar o SSH que por padrão vem desabilitada, para facilitar a transferência e comunicação remota entre os dispositivos, configurar o espaço de memória para otimizar a reprodução de vídeo e ajustar a resolução para Full HD.
	Essas configurações foram realizadas através da interface de configuração do dispositivo no terminal:

	$ sudo raspi-config

O boot de sistema sem interface gráfica pode ser configurado pela opção 3 Boot Options então selecionada a opção B1 Desktop/CLI, habilitando a opção B2 Console Autologin. A configuração do SSH fica dentro da opção 5 Interacing Options, então P2 SSH selecionando Enable. A memória pode ser configurada através do item 7 Advanced Options, selecionando A3 Memory Split e colocando o valor 256. Também dentro da opção 7 Advanced Options deve ser acessado o item A5 Resolution e selecionado CEA Mode 16 1920x1080 16:9. Ao final o sistema precisa ser reiniciado.
Após o reboot é necessário atualizar o sistema, para isso, utiliza-se os seguintes comandos (requer conexão com a internet):

	$ sudo apt-get clean
	$ sudo apt-get update
	$ sudo apt-get upgrade

No RPi laboratório foi feito o download e foi descompactado o openFrameworks para o desenvolvimento da aplicação de reprodução de vídeo e da aplicação de sincronização e controle.

	$ wget http://openframeworks.cc/versions/v0.9.8/of_v0.9.8_linuxarmv6l_release.tar.gz
	$ mkdir openFrameworks
	$ tar vxfz of_v0.9.8_linuxarmv6l_release.tar.gz -C openFrameworks --strip-components 1

Em seguida é necessária a execução dos scripts de dependência de bibliotecas. Esses arquivos podem ser encontrados dentro de /openFrameworks/scripts/linux/debian.

	$ sudo ./install_dependencies.sh
	$ sudo ./install_codecs.sh

Por fim o openFrameworks é compilado. Este processo pode ser acelerado utilizando o 4 cores do processador através do argumento –j4 depois do comando make.

	$ make -j4 Release -C openFrameworks/libs/openFrameworksCompiled/

Após a configuração o RPi estará pronto para utilizar o framework!
