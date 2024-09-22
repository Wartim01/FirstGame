import os

# Dossier racine de votre projet
root_folder = "MonJeu"

# Sous-dossiers à créer
folders = [
    "include", 
    "include/Game.h", 
    "include/Entity.h", 
    "include/Component.h", 
    "include/Engine.h",
    "src", 
    "src/Game.cpp", 
    "src/Entity.cpp", 
    "src/Component.cpp", 
    "src/Engine.cpp",
    "assets", 
    "assets/textures", 
    "assets/models", 
    "assets/sounds", 
    "assets/fonts", 
    "build", 
    "scripts", 
    "docs"
]

# Fonction pour créer les dossiers
def create_folders(base_path, folders):
    for folder in folders:
        path = os.path.join(base_path, folder)
        os.makedirs(path, exist_ok=True)
        print(f"Création de {path}")

# Exécution de la fonction
create_folders(root_folder, folders)
