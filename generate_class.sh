#!/bin/bash

# Vérifier si un argument a été fourni
if [ $# -ne  2 ]; then
	echo "Usage: $0 ClassName COLOR"
	exit  1
fi

# Récupérer le nom de la classe depuis l'argument
CLASS_NAME=$1
COLOR=$2

# Convertir le nom de la classe en une macro de protection d'inclusion unique
INCLUDE_GUARD=$(echo $CLASS_NAME | tr '[:lower:]' '[:upper:]')
INCLUDE_GUARD="DEF_${INCLUDE_GUARD}"

# Construire le .hpp
CLASS_HEADER="#ifndef ${INCLUDE_GUARD}
#define ${INCLUDE_GUARD}

#define RED \"\033[31m\"
#define YELLOW \"\033[33m\"
#define VIOLET \"\033[35m\"
#define GREEN \"\033[32m\"
#define LGREEN \"\033[92m\"
#define BLUE \"\033[34m\"
#define WHITE \"\033[37m\"
#define BLACK \"\033[30m\"
#define CYAN \"\033[36m\"
#define MAGENTA \"\033[35m\"
#define RESET \"\033[0m\"

#include <iostream>

class $CLASS_NAME
{
	public:
		$CLASS_NAME();
		$CLASS_NAME($CLASS_NAME const& src);
		~$CLASS_NAME();
		$CLASS_NAME &operator=($CLASS_NAME const& src);

	private:
		// Ajoutez  ici les membres de données

};

std::ostream &operator<<(std::ostream &o, $CLASS_NAME const& src);

#endif
"


# Construire le .cpp
CLASS_CONTENT="#include \"$CLASS_NAME.hpp\"

$CLASS_NAME::$CLASS_NAME()
{
	std::cout << $COLOR << \"Default $CLASS_NAME\" << RESET << \" has been created\" << std::endl;
}

$CLASS_NAME::$CLASS_NAME($CLASS_NAME const& src) // A completer
{
	std::cout << $COLOR << \"Copy $CLASS_NAME \" << RESET << \" has been created\" << std::endl;
}

$CLASS_NAME::~$CLASS_NAME()
{
	std::cout << $COLOR << \"$CLASS_NAME \" << RESET << \" has been destroyed\" << std::endl;
}

$CLASS_NAME & $CLASS_NAME::operator=($CLASS_NAME const& src)
{
	if (this != &src)
		// A completer
	return *this;
}

std::ostream &operator<<(std::ostream &o, $CLASS_NAME const& src)
{
	o << $COLOR << \"$CLASS_NAME \";// A completer
	o << RESET << std::endl;
	return o;
}
"

# Créer le fichier de classe avec le contenu généré
echo "$CLASS_HEADER" > "${CLASS_NAME}.hpp"
echo "$CLASS_CONTENT" > "${CLASS_NAME}.cpp"

# Afficher un message de confirmation
echo "Les fichiers pour la $CLASS_NAME ont été créées."
