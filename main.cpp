#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <cmath>

using namespace std;

const int MAX_USERS = 5;

struct user
{
    string name;
    string password;
};

void createAcc();
bool login();
void modifyAcc();
void startMenu();
void exercises();
void title();
void diagnostico();
void weight();
void routine();

int main()
{
    bool success = false; // si el login tiene exito no vuelve a entrar en el bucle gracias a esta var

    int elecc;

    do
    {
        title();

        cout << "Que quieres hacer?" << endl;
        cout << endl;
        cout << "\t1 - Iniciar sesion" << endl;
        cout << "\t2 - Crear cuenta" << endl;
        cout << "\t3 - Modificar cuenta" << endl;
        cout << "\t0 - Salir del programa" << endl;
        cin >> elecc;

        while (cin.fail())
        {

            cout << "Por favor introduce una opcion valida" << endl;
            cin.clear();
            cin.ignore();
            cin >> elecc;
        }

        if (elecc == 2)
        {
            Sleep(500);
            system("cls");
            createAcc();
        }
        else if (elecc == 3)
        {
            Sleep(500);
            system("cls");
            modifyAcc();
        }
        else if (elecc == 1)
        {
            Sleep(500);
            system("cls");
            success = login();

            if (success == true)
            {
                startMenu();
            }
        }
        else if (elecc == 0)
        {
            cout << "Cerrando el programa...";
            Sleep(1000);
        }
        else
        {
            cout << "Por favor, introduzca una opcion valida" << endl;
            Sleep(1000);
            system("cls");
        }

    } while (elecc != 0);

    system("DOCUMENTACION\\logo.jpg");

    system("cls");

    return 0;
}

/*
Lee users.txt si hay menos de 5 cuentas creadas, permite crear nuevas. Para ello pedira un nombre y una contraseña y los guardara en primer lugar 
en la posicion donde haya un 0 guardado (cuenta eliminada) y al final del txt si no hay cuenta eliminada.

-Entradas: none
-Salidas: none

*/
void createAcc()
{
    user users[MAX_USERS];
    string nameTemp;
    string passTemp;
    int numUsers = 0;
    int deleteAcc = 0;
    int posDeleteAcc;
    int cont = -1;

    ifstream fileRead;

    fileRead.open("users.txt");

    if (fileRead.is_open())
    {
        bool WhileBanner = false;

        while (numUsers + deleteAcc < MAX_USERS && WhileBanner == false) //lee el fichero 5 veces o cuando este se acabe
        {
            fileRead >> users[numUsers + deleteAcc].name >> users[numUsers + deleteAcc].password;

            if (fileRead.eof() == true)
            {
                WhileBanner = true;
            }
            else
            {
                cont++;

                if (users[numUsers].name != "0")
                {
                    numUsers++;
                }
                else
                {
                    posDeleteAcc = cont; //guarda la posicion en la que hay una cuenta borrada
                    deleteAcc++;
                }
            }
        }
    }
    else
    {
        cout << "No se ha podido acceder a los datos, por favor contacte con el servicio de atencion al cliente";
    }

    fileRead.close();

    if (numUsers < MAX_USERS) // condicion para que si no hay hueco no se puedan guardar mas cuentas
    {
        bool nameExist = false;

        do
        {
            title();

            do
            {
                cout << "El nombre de usuario debe tener al menos dos caracteres." << endl;
                cout << endl;
                cout << "\tNombre de usuario: ";
                cin >> nameTemp;

                for (int i = 0; i < 5; i++) // con este bucle comprobamos si el nameTemp ya está en el fichero
                {

                    if (nameTemp == users[i].name)
                    {
                        nameExist = true;
                        i = 5;
                    }
                    else
                    {
                        nameExist = false;
                    }
                }
            } while (nameTemp.size() < 2);

            if (nameExist)
            {
                cout << "Nombre de usuario no disponible, intentelo de nuevo" << endl;
                Sleep(1000);
                system("cls");
            }
            else
            {
                cout << "Nombre de usuario valido" << endl;
                cout << endl;
            }

        } while (nameExist == true);

        char pass1;
        string passTemp2;

        do
        {
            do
            {
                passTemp = ""; // vaciamos la var para resetearla en cada iteracion del do while
                cout << "La password debe tener al menos dos caracteres." << endl;
                cout << endl;
                cout << "\tPassword: ";

                pass1 = getch(); // funcion que coge un char sin mostrarlo por pantalla

                while (pass1 != 13) // 13 es el ascii del enter
                {
                    if (pass1 != 8) // 8 es el ascii de la tecla retroceso
                    {

                        passTemp.push_back(pass1); // guardamos el char en la ultima pos de passTemp y mostramos un * por display
                        cout << "*";
                    }
                    else
                    {
                        if (passTemp.size() > 0) // condicion para evitar que borremos mas cosas del display
                        {
                            cout << "\b \b";     // movemos cursos hacia atras, mostramos espacio blanco (cursor se mueve adelante), movemos again el curso patras
                            passTemp.pop_back(); // eliminamos el ultimo elemento del string passTemp, en este caso el espacio en blanco
                        }
                    }

                    pass1 = getch();
                }

                cout << endl;

            } while (passTemp.size() < 2);

            passTemp2 = "";
            cout << "\tRepita su password: ";
            pass1 = getch();

            while (pass1 != 13)
            {

                if (pass1 != 8)
                {

                    passTemp2.push_back(pass1);
                    cout << "*";
                }
                else
                {

                    if (passTemp.size() > 0)
                    {
                        cout << "\b \b";
                        passTemp.pop_back();
                    }
                }

                pass1 = getch();
            }

            cout << endl;

            if (passTemp2 == passTemp) // si ambas contraseñas coinciden se guardan los datos en el fichero
            {
                if (deleteAcc == 0)
                {
                    users[numUsers].name = nameTemp;
                    users[numUsers].password = passTemp;

                    ofstream fileWrite;

                    fileWrite.open("users.txt", ios::app);

                    fileWrite << users[numUsers].name << " " << users[numUsers].password << endl;

                    fileWrite.close();
                }
                else
                {
                    users[posDeleteAcc].name = nameTemp;
                    users[posDeleteAcc].password = passTemp;

                    ofstream fileWrite;

                    fileWrite.open("users.txt");

                    for (int i = 0; i < numUsers + deleteAcc; i++)
                    {

                        fileWrite << users[i].name << " " << users[i].password << endl;
                    }

                    fileWrite.close();
                }
                cout << endl;
                cout << "\t\tCuenta creada satisfactoriamente" << endl;
            }
            else
            {

                cout << "Las password no coinciden, intentelo de nuevo" << endl;
                Sleep(1000);
                system("cls");
            }

        } while (passTemp2 != passTemp);
    }
    else
    {
        title();
        cout << "No se pueden guardar mas usuarios" << endl;
    }

    Sleep(1200);
    system("cls");
}

/*
Lee el users.txt y pregunta por un usuario y una contraseña, permite saber si los credenciales son correctos a través de un booleano

-Entradas: none
-Salidas: true/false

*/

bool login()
{
    user users[MAX_USERS];
    string nameTemp;
    string passTemp;
    int numUsers = 0;
    int deleteAcc = 0;
    int posDeleteAcc;
    int cont = -1;

    ifstream fileRead;

    fileRead.open("users.txt");

    if (fileRead.is_open())
    {
        bool WhileBanner = false;

        while (numUsers + deleteAcc < MAX_USERS && WhileBanner == false)
        {
            fileRead >> users[numUsers + deleteAcc].name >> users[numUsers + deleteAcc].password;

            if (fileRead.eof() == true)
            {
                WhileBanner = true;
            }
            else
            {
                if (users[numUsers].name != "0")
                {
                    numUsers++;
                }
                else
                {
                    posDeleteAcc = cont;
                    deleteAcc++;
                }
            }
        }
    }
    else
    {

        cout << "No se ha podido acceder a los datos, por favor contacte con el servicio de atencion al cliente";
    }

    fileRead.close();

    int contIntentos = 0;
    bool success = false;

    if (numUsers > 0)
    {
        do
        {
            title();

            cout << "\tIntroduzca su nombre de usuario: ";
            cin >> nameTemp;

            cout << endl;

            cout << "\tIntroduzca su password: ";

            char pass1;

            passTemp = "";

            pass1 = getch(); // funcion que coge un char sin mostrarlo por pantalla

            while (pass1 != 13) // 13 es el ascii del enter
            {

                if (pass1 != 8) // 8 es el ascii de la tecla retroceso
                {
                    passTemp.push_back(pass1); // guardamos el char en la ultima pos de passTemp y mostramos un * por display
                    cout << "*";
                }
                else
                {
                    if (passTemp.size() > 0) // condicion para evitar que borremos mas cosas del display
                    {
                        cout << "\b \b";     // movemos cursos hacia atras, mostramos espacio blanco (cursor se mueve adelante), movemos again el curso patras
                        passTemp.pop_back(); // eliminamos el ultimo elemento del string passTemp, en este caso el espacio en blanco
                    }
                }

                pass1 = getch();
            }

            cout << endl;

            bool AccExist = false;

            for (int i = 0; i < numUsers + deleteAcc; i++) // con este bucle comprobamos si el nameTemp ya está en el fichero
            {

                if (nameTemp == users[i].name && passTemp == users[i].password && nameTemp != "0" && passTemp != "0") // para evitar que si introduce 0 0 inicie sesion
                {
                    AccExist = true;
                    i = 5;
                }
                else
                {
                    AccExist = false;
                }
            }

            if (AccExist)
            {
                cout << endl;
                cout << "\t\t\t\t\t\t\t\tBIENVENIDO A FESAC FITNES APP, " << nameTemp << "!!" << endl;
                cout << "\t\t\t\t\t\t\tLa aplicacion creada por, pero NO para desarrolladores!!";
                success = true;
                string nameuser[1];
                nameuser[0] = nameTemp;
                Sleep(3500);
                system("cls");
            }
            else
            {
                cout << "Nombre de usuario y/o password incorrectos, le quedan " << 2 - contIntentos << " intentos." << endl;
                contIntentos++;
                success = false;
                Sleep(1000);
                system("cls");
            }

        } while (contIntentos < 3 && success == false);
    }
    else
    {
        title();
        cout << "Todavia no hay ningun usuario registrado" << endl;
    }

    Sleep(1000);
    system("cls");
    return success;
}

/*
Dependiendo de la eleccion del usuario permite acceder a una funcion u a otra.

-Entradas: none
-Salidas: none

*/

void startMenu()
{
    int elecc;

    do
    {
        title();

        cout << "Que quieres hacer?" << endl;
        cout << endl;
        cout << "\t1 - Tutoriales de ejercicios" << endl;
        cout << "\t2 - Crea tu propia rutina de entrenamiento" << endl;
        cout << "\t3 - Diagnostico" << endl;
        cout << "\t4 - Evolucion de tu peso en el ultimo anio y medio (maximo 148kg): " << endl;
        cout << "\t0 - Cerrar sesion" << endl;
        cin >> elecc;

        while (cin.fail())
        {

            cout << "Por favor introduce una opcion valida" << endl;
            cin.clear();
            cin.ignore();
            cin >> elecc;
        }

        if (elecc == 1)
        {
            system("cls");
            exercises();
        }
        else if (elecc == 2)
        {
            system("cls");
            routine();
        }
        else if (elecc == 3)
        {
            system("cls");
            diagnostico();
        }
        else if (elecc == 4)
        {
            system("cls");
            weight();
        }
        else if (elecc == 0)
        {
            cout << "Cerrando sesion...";
        }
        else
        {
            cout << "Por favor, introduzca una opcion valida" << endl;
            Sleep(1000);
            system("cls");
        }

    } while (elecc != 0);

    Sleep(1000);
    system("cls");
}

/*
Lee el fichero users.txt y guarda los datos en un array.
Permite cambiar el nombre de usuario, pide el nombre de la cuenta que quiere cambiar recorre el array con un for y si coinciden guarda el subindice, despues de pedir la contraseña y que tambien coincida permite cambiar el nombre de la posicion guardada previamente, al final reescribe users,txt
Permite cambiar la contraseña de una cuenta, sigue la misma logica que para cambiar el nombre de usuario.
Permite eliminar cuentas, misma logica que los dos anteriores pero guarda como 0 el usuario y la contraseña de la posicion guardada

-Entradas: none
-Salidas: none

*/

void modifyAcc()
{
    user users[MAX_USERS];
    string nameTemp;
    string passTemp;
    int numUsers = 0;
    int deleteAcc = 0;
    int posDeleteAcc;
    int cont = -1;

    ifstream fileRead;

    fileRead.open("users.txt");

    if (fileRead.is_open())
    {

        bool WhileBanner = false;

        while (numUsers + deleteAcc < MAX_USERS && WhileBanner == false)
        {
            fileRead >> users[numUsers + deleteAcc].name >> users[numUsers + deleteAcc].password;

            if (fileRead.eof() == true)
            {
                WhileBanner = true;
            }
            else
            {
                cont++;

                if (users[numUsers].name != "0")
                {
                    numUsers++;
                }
                else
                {
                    posDeleteAcc = cont;
                    deleteAcc++;
                }
            }
        }
    }
    else
    {

        cout << "No se ha podido acceder a los datos, por favor contacte con el servicio de atencion al cliente";
    }

    fileRead.close();

    int elecction;
    string newName;
    int contador = 0;

    do
    {
        title();

        cout << "Que quieres hacer?" << endl;
        cout << "1 - Cambiar nombre de usuario" << endl;
        cout << "2 - Cambiar password" << endl;
        cout << "3 - Eliminar cuenta" << endl;
        cout << "0 - Volver" << endl;
        cin >> elecction;

        while (cin.fail())
        {

            cout << "Por favor introduce una opcion valida" << endl;
            cin.clear();
            cin.ignore();
            cin >> elecction;
        }

        if (elecction == 1)
        {

            bool nameExist = false;
            bool exit;
            int position; // guardaremos el subindice para saber que nombre del array tenemos que cambiar

            do
            {
                cout << "Introduzca el nombre de usuario de la cuenta que quieres modificar: ";
                cin >> newName;

                for (int i = 0; i < numUsers + deleteAcc; i++)
                {

                    if (newName == users[i].name)
                    {

                        nameExist = true;
                        position = i;
                        i = numUsers + deleteAcc;
                    }
                }

                if (nameExist == false)
                {

                    cout << "No existe una cuenta con ese usuario" << endl;
                    cout << "1 - Volver a intentar" << endl;
                    cout << "0 - Volver al menu" << endl;
                    int elecc;
                    cin >> elecc;

                    if (elecc == 1)
                    {
                        exit = false;
                    }
                    else if (elecc == 0)
                    {
                        exit = true;
                    }
                }

            } while (nameExist == false && exit == false);

            if (!exit) // si el usuario no ha intentado salir, entra
            {
                do
                {
                    cout << "A continuacion introduzca la password: ";
                    char pass1;

                    passTemp = "";

                    pass1 = getch();

                    while (pass1 != 13)
                    {

                        if (pass1 != 8)
                        {

                            passTemp.push_back(pass1);
                            cout << "*";
                        }
                        else
                        {

                            if (passTemp.size() > 0)
                            {
                                cout << "\b \b";
                                passTemp.pop_back();
                            }
                        }

                        pass1 = getch();
                    }

                    bool passExist = false;

                    for (int i = 0; i < numUsers + deleteAcc; i++)
                    {

                        if (passTemp == users[i].password)
                        {
                            passExist = true;
                            i = numUsers + deleteAcc;
                        }
                    }

                    cout << endl;

                    if (passExist == false)
                    {

                        cout << "Password incorrecta, le quedan " << 3 - contador << " intentos." << endl;
                        contador++;
                    }
                    else
                    {
                        bool sameName = false;

                        do
                        {
                            cout << "Le recordamos que el nombre de usuario debe tener al menos dos caracteres." << endl;
                            cout << "Introduzca el nuevo nombre de usuario: ";
                            cin >> newName;

                            if (users[position].name == newName)
                            {
                                sameName = true;
                                cout << "El nuevo nombre de usuario no puede coincidir con el anterior" << endl;
                            }
                            else
                            {

                                sameName = false;
                            }

                        } while (sameName == true || newName.size() < 2);

                        Sleep(200);
                        system("cls");

                        users[position].name = newName;

                        cout << "Nombre de usuario cambiado con exito, " << newName << endl;

                        contador = 3;
                    }

                } while (cont < 3);

                // abrimos flujo de escritura y sobreescribimos el txt con las modificaciones que se hayan hecho

                ofstream fileWrite;

                fileWrite.open("users.txt");

                for (int i = 0; i < numUsers + deleteAcc; i++)
                {

                    fileWrite << users[i].name << " " << users[i].password << endl;
                }

                fileWrite.close();
            }
            else
            {
                cout << "Volviendo al menu...";
                Sleep(1000);
                system("cls");
            }
        }
        else if (elecction == 2)
        {
            cout << "Introduzca el nombre de usuario de la cuenta que quieres modificar: ";
            cin >> newName;

            bool nameExist = false;

            for (int i = 0; i < numUsers + deleteAcc; i++)
            {
                if (newName == users[i].name)
                {
                    nameExist = true;
                    i = numUsers;
                }
            }

            if (nameExist == false)
            {
                cout << "No existe una cuenta con ese usuario" << endl;
                Sleep(500);
                system("cls");
            }
            else
            {
                do
                {
                    cout << "A continuacion introduzca la password actual: ";
                    char pass1;

                    passTemp = "";

                    pass1 = getch();

                    while (pass1 != 13)
                    {

                        if (pass1 != 8)
                        {

                            passTemp.push_back(pass1);
                            cout << "*";
                        }
                        else
                        {

                            if (passTemp.size() > 0)
                            {
                                cout << "\b \b";
                                passTemp.pop_back();
                            }
                        }

                        pass1 = getch();
                    }

                    bool passExist = false;

                    int position; // guardaremos el subindice para saber que pass del array tenemos que cambiar

                    for (int i = 0; i < numUsers + deleteAcc; i++)
                    {
                        if (passTemp == users[i].password && newName == users[i].name) // por si hay dos cuentas con la misma contraseña añadimos la segunda condicion
                        {
                            passExist = true;
                            position = i;
                            i = numUsers;
                        }
                    }

                    cout << endl;

                    if (passExist == false)
                    {

                        cout << "Password incorrecta, le quedan " << 3 - cont << " intentos." << endl;
                        cont++;
                    }
                    else
                    {
                        bool samePass = false;

                        do
                        {
                            cout << "Le recordamos que la password debe tener al menos dos caracteres." << endl;
                            cout << "Introduzca la nueva password: ";
                            cin >> passTemp;

                            if (users[position].password == passTemp)
                            {
                                samePass = true;
                                cout << "La password nueva debe ser diferente a la original" << endl;
                            }
                            else
                            {
                                samePass = false;
                            }

                        } while (samePass == true || passTemp.size() < 2);

                        users[position].password = passTemp;

                        cout << "Password cambiada con exito" << endl;

                        cont = 4;
                    }

                } while (cont < 3);

                system("cls");

                if (cont == 4)
                {
                    ofstream fileWrite;

                    fileWrite.open("users.txt");

                    for (int i = 0; i < numUsers + deleteAcc; i++)
                    {
                        fileWrite << users[i].name << " " << users[i].password << endl;
                    }

                    fileWrite.close();
                }
            }
        }
        else if (elecction == 3)
        {
            do
            {
                char file[100];

                cout << "Introduzca el nombre de usuario de la cuenta que quiere eliminar: ";
                cin >> file; // usaremos este array para borrar los archivos de esta cuenta en caso de que existiesen

                nameTemp = file;

                cout << "Introduzca la password: ";
                char pass1;

                passTemp = "";

                pass1 = getch(); // funcion que coge un char sin mostrarlo por pantalla

                while (pass1 != 13) // 13 es el ascii del enter
                {

                    if (pass1 != 8) // 8 es el ascii de la tecla retroceso
                    {

                        passTemp.push_back(pass1); // guardamos el char en la ultima pos de passTemp y mostramos un * por display
                        cout << "*";
                    }
                    else
                    {

                        if (passTemp.size() > 0) // condicion para evitar que borremos mas cosas del display
                        {
                            cout << "\b \b";     // movemos cursos hacia atras, mostramos espacio blanco (cursor se mueve adelante), movemos again el curso patras
                            passTemp.pop_back(); // eliminamos el ultimo elemento del string passTemp, en este caso el espacio en blanco
                        }
                    }

                    pass1 = getch();
                }

                cout << endl;

                bool AccExist = false;
                int posAcc; // para saber en que posicion se encuentra dicha cuenta

                for (int i = 0; i < numUsers + deleteAcc; i++) // con este bucle comprobamos si el nameTemp ya está en el  fichero
                {
                    if (nameTemp == users[i].name && passTemp == users[i].password)
                    {
                        AccExist = true;
                        posAcc = i;
                        i = 5;
                    }
                    else
                    {
                        AccExist = false;
                    }
                }

                if (AccExist)
                {
                    int longitud = nameTemp.size();

                    file[longitud] = '.';
                    file[longitud + 1] = 't';
                    file[longitud + 2] = 'x';
                    file[longitud + 3] = 't'; // añadimos la extension .txt para que se pueda borrar

                    users[posAcc].name = "0";
                    users[posAcc].password = "0";

                    ofstream fileWrite;

                    fileWrite.open("users.txt");

                    for (int i = 0; i < numUsers + deleteAcc; i++)
                    {

                        fileWrite << users[i].name << " " << users[i].password << endl;
                    }

                    fileWrite.close();

                    cout << "Cuenta eliminada con exito, volviendo al menu..." << endl;
                    cont = 3;

                    Sleep(500);
                    remove(file);
                    system("cls");
                }
                else
                {
                    cout << "Nombre de usuario y/o password incorrectos, le quedan " << 2 - cont << " intentos." << endl;
                    cont++;
                }

            } while (cont < 3);

            Sleep(500);
            system("cls");
        }
        else if (elecction == 0)
        {
            cout << "Volviendo al menu..." << endl;
            Sleep(1000);
            system("cls");
        }
        else
        {
            cout << "Por favor, introduzca una opcion valida" << endl;
            Sleep(1000);
            system("cls");
        }
    } while (elecction != 0);

    Sleep(300);
}

/*
Segun la eleccion del usuario muestra un ejercicio u otro. 
El primero con un while y usando la funcion Sleep y system("cls") simulo a un hombre corriendo, con un contador controlo el tiempo que dura dicha funcion

-Entradas: none
-Salidas: none

*/

void exercises()
{

    int elecc;

    do
    {
        title();

        cout << "Que quieres ver?" << endl;
        cout << endl;
        cout << "\t1 - Calentamiento" << endl;
        cout << "\t2 - Cruce polea alta" << endl;
        cout << "\t3 - Elevaciones laterales" << endl;
        cout << "\t4 - Jalon al pecho" << endl;
        cout << "\t5 - Peso muerto convencional" << endl;
        cout << "\t6 - Press Banca" << endl;
        cout << "\t7 - Press Militar con mancuernas" << endl;
        cout << "\t8 - Remo con mancuernas" << endl;
        cout << "\t9 - Sentadillas" << endl;
        cout << "\t0 - Volver al inicio" << endl;
        cin >> elecc;

        while (cin.fail())
        {

            cout << "Por favor introduce una opcion valida" << endl;
            cin.clear();
            cin.ignore();
            cin >> elecc;
        }

        if (elecc == 1)
        {
            int cont = 15;

            while (cont >= 0)
            {
                cout << "    ___ 0" << endl;
                cout << "   |   /\\ " << endl;
                cout << "      /  \\__ " << endl;
                cout << "  ___/\\ " << endl;
                cout << " |     \\ " << endl;
                cout << "        \\_" << endl;
                cout << "----------.--------------.---------.-";
                Sleep(150);
                system("cls");

                cout << "         " << endl;
                cout << "        0" << endl;
                cout << "       / " << endl;
                cout << "      /|_ " << endl;
                cout << "    _/| " << endl;
                cout << "   |  | " << endl;
                cout << "      |_" << endl;
                cout << "-----.--------.--------.-------------";
                Sleep(150);
                system("cls");

                cout << "        0" << endl;
                cout << "     __/\\ " << endl;
                cout << "    | /  \\_ " << endl;
                cout << "     /\\ " << endl;
                cout << "    / |_ " << endl;
                cout << "   /_  " << endl;
                cout << "-------.--------.-------------------";
                Sleep(150);
                system("cls");

                cont--;
            }
        }
        else if (elecc == 2)
        {
            system("videos\\CrucedePoleaPectorales.mp4");
            system("cls");
        }
        else if (elecc == 3)
        {
            system("videos\\ElevacionesLateralesHombro.mp4");
            system("cls");
        }
        else if (elecc == 4)
        {
            system("videos\\jalonespalda.mp4");
            system("cls");
        }
        else if (elecc == 5)
        {
            system("videos\\PesomuertotradicionalPierna.mp4");
            system("cls");
        }
        else if (elecc == 6)
        {
            system("videos\\PressdeBancaPectorales.mp4");
            system("cls");
        }
        else if (elecc == 7)
        {
            system("videos\\PressMilitarMancuernaHombro.mp4");
            system("cls");
        }
        else if (elecc == 8)
        {
            system("videos\\RemoconMancuernaEspalda.mp4");
            system("cls");
        }
        else if (elecc == 9)
        {
            system("videos\\SentadillasPierna.mp4");
            system("cls");
        }
        else if (elecc == 0)
        {
            cout << "Volviendo al menu..." << endl;
        }
        else
        {
            cout << "Por favor, introduzca una opcion valida" << endl;
            Sleep(1000);
            system("cls");
        }

    } while (elecc != 0);

    Sleep(1000);
    system("cls");
}

/*
Funcion con el logo de la supuesta aplicacion. Muestra por pantalla
*/

void title()
{

    cout << "\t _______  _______     _______.     ___       ______     _______  __  .___________..__   __.  _______     _______.    _______.        ___      .______  .______" << endl;
    cout << "\t|   ____||   ____|   /       |    /   \\     /      |   |   ____||  | |           ||  \\ |  | |   ____|   /       |   /       |       /   \\     |   _  \\ |   _  \\" << endl;
    cout << "\t|  |__   |  |__     |   (----`   /  ^  \\   |  ,----'   |  |__   |  | `---|  |----`|   \\|  | |  |__     |   (----`  |   (----`      /  ^  \\    |  |_)  ||  |_)  |" << endl;
    cout << "\t|   __|  |   __|     \\   \\      /  /_\\  \\  |  |        |   __|  |  |     |  |     |  . `  | |   __|     \\   \\       \\   \\         /  /_\\  \\   |   ___/ |   ___/" << endl;
    cout << "\t|  |     |  |____.----)   |    /  _____  \\ |  `----.   |  |     |  |     |  |     |  |\\   | |  |____.----)   |  .----)   |       /  _____  \\  |  |     |  |" << endl;
    cout << "\t|__|     |_______|_______/    /__/     \\__\\ \\______|   |__|     |__|     |__|     |__| \\__| |_______|_______/   |_______/       /__/     \\__\\ | _|     | _|" << endl;
    cout << endl;
}

/*
Te pide una serie de datos y los almacena en un array, cada dato se guarda en una posicion determinada y segun una serie de condicionales se obtienen unas conclusiones
Escribe los datos del array en un fichero txt 'diagnostico' y despues lo muestra por pantalla

-Entradas: none
-Salidas: none

*/

void diagnostico()
{

    float datos[5];
    int gen;

    title();

    cout << "\tVamos a realizar el calculo de dos indices como son el Indice de Masa Corporal(IMC), que establece una relacion entre su peso y" << endl;
    cout << "\taltura para determinar si se encuentra en valores saludables, y el Indice de Cintura-Cadera, el cual establece una relacion entre " << endl;
    cout << "\tla circunferencia de su cintura y de su cadera y establecera un valor para medir el riesgo de padecer enfermedades como pueden ser diabetes mellitus, " << endl;
    cout << "\tenfermedades coronarias o alteraciones de la tension arterial." << endl;
    cout << endl;
    cout << "\tPara ello le vamos a solicitar la siguiente informacion: " << endl;
    cout << endl;

    cout << "\t";
    system("pause");

    cout << "\tAltura(m)(ej: 1.72): ";
    cin >> datos[0];
    cout << endl;

    cout << "\tPeso(kg): ";
    cin >> datos[1];
    cout << endl;

    datos[2] = (datos[1]) / (pow(datos[0], 2));

    cout << "\tSexo:" << endl;
    cout << "\t1 - Hombre";
    cout << "\t2 - Mujer";
    cout << "\t";
    cin >> gen;
    cout << endl;

    cout << "\tCircunferencia de la cintura(cm): ";
    cin >> datos[3];
    cout << endl;

    cout << "\tCircunferencia de la cadera(cm): ";
    cin >> datos[4];
    cout << endl;

    datos[5] = datos[3] / datos[4];

    cout << "\tGENERANDO INFORME...";
    Sleep(500);
    system("cls");

    ofstream fileWrite;

    fileWrite.open("diagnostico.txt");

    fileWrite << "\t\t====IMC====" << endl;
    fileWrite << "\tAltura(m): " << datos[0] << endl;
    fileWrite << "\tPeso(kg): " << datos[1] << endl;
    fileWrite << "\tIMC: " << datos[2] << endl;

    if (datos[2] < 18.5)
    {
        fileWrite << "\tResultado: Peso bajo" << endl;
    }
    else if (datos[2] >= 18.5 && datos[2] < 24.9)
    {
        fileWrite << "\tResultado: Peso normal" << endl;
    }
    else if (datos[2] >= 25 && datos[2] < 29.9)
    {

        fileWrite << "\tResultado: Sobrepeso" << endl;
    }
    else if (datos[2] >= 30)
    {

        fileWrite << "\tResultado: Obesidad" << endl;
    }

    fileWrite << "\t\t====ICC====" << endl;
    fileWrite << "\tCircunferencia de la Cintura(cm): " << datos[3] << endl;
    fileWrite << "\tCircunferencia de la cadera(cm): " << datos[4] << endl;
    fileWrite << "\tICC: " << datos[5] << endl;

    if (gen == 1)
    {

        if (datos[5] <= 0.95)
        {

            fileWrite << "\tRiesgo: Bajo" << endl;
        }
        else if (datos[5] >= 0.96 && datos[5] <= 1)
        {

            fileWrite << "\tRiesgo: Moderado" << endl;
        }
        else if (datos[5] > 1)
        {

            fileWrite << "\tRiesgo: Alto" << endl;
        }
    }
    else if (gen == 2)
    {

        if (datos[5] <= 0.8)
        {

            fileWrite << "\tRiesgo: Bajo" << endl;
        }
        else if (datos[5] >= 0, 81 && datos[5] <= 0, 85)
        {

            fileWrite << "\tRiesgo: Moderado" << endl;
        }
        else if (datos[5] >= 0, 86)
        {

            fileWrite << "\tRiesgo: Alto" << endl;
        }
    }

    fileWrite.close();

    cout << "\t\t====IMC====" << endl;
    cout << "\tAltura(m): " << datos[0] << endl;
    cout << "\tPeso(kg): " << datos[1] << endl;
    cout << "\tIMC: " << datos[2] << endl;

    if (datos[2] < 18.5)
    {
        cout << "\tResultado: Peso bajo" << endl;
    }
    else if (datos[2] >= 18.5 && datos[2] < 24.9)
    {
        cout << "\tResultado: Peso normal" << endl;
    }
    else if (datos[2] >= 25 && datos[2] < 29.9)
    {

        cout << "\tResultado: Sobrepeso" << endl;
    }
    else if (datos[2] >= 30)
    {

        cout << "\tResultado: Obesidad" << endl;
    }

    cout << "\t\t====ICC====" << endl;
    cout << "\tCircunferencia de la Cintura(cm): " << datos[3] << endl;
    cout << "\tCircunferencia de la cadera(cm): " << datos[4] << endl;
    cout << "\tICC: " << datos[5] << endl;

    if (gen == 1)
    {

        if (datos[5] <= 0.95)
        {

            cout << "\tRiesgo: Bajo" << endl;
        }
        else if (datos[5] >= 0.96 && datos[5] <= 1)
        {

            cout << "\tRiesgo: Moderado" << endl;
        }
        else if (datos[5] > 1)
        {

            cout << "\tRiesgo: Alto" << endl;
        }
    }
    else if (gen == 2)
    {

        if (datos[5] <= 0.8)
        {

            cout << "\tRiesgo: Bajo" << endl;
        }
        else if (datos[5] >= 0, 81 && datos[5] <= 0, 85)
        {

            cout << "\tRiesgo: Moderado" << endl;
        }
        else if (datos[5] >= 0, 86)
        {

            cout << "\tRiesgo: Alto" << endl;
        }
    }

    cout << endl;
    cout << "Se ha generado una copia en el fichero 'diagnostico.txt'." << endl;

    system("pause");
    system("cls");
}

/*
Segun las elecciones del usuario crea o lee un array bidimensional que es una representacion grafica de la evolucion del peso semanal del usuario.
Permite ver la evolucion leyendo y mostrando por pantalla el fichero que se crea con el nombre del propio usuario. Si aun no hay fichero indica que aun no hay historial.
Permite agregar un peso a la grafica, si aun no hay fichero crea un array bidimensional de 76 x 76 donde la fila 0 son "_" y la columna 0 y 1 indican peso 0, la mitad 
del eje Y y el tope del eje Y. Las filas van de 2 en 2 hasta 74 (maximo 148kg). Si ya existe el fichero, lo lee y permite agregar un peso nuevo.

-Entradas: none
-Salidas: none

*/

void weight()
{
    user users[MAX_USERS];
    string nameTemp;
    int numUsers = 0;
    int deleteAcc = 0;

    ifstream fileRead;

    fileRead.open("users.txt");

    if (fileRead.is_open())
    {
        bool WhileBanner = false;

        while (numUsers + deleteAcc < MAX_USERS && WhileBanner == false)
        {
            fileRead >> users[numUsers + deleteAcc].name >> users[numUsers + deleteAcc].password;

            if (fileRead.eof() == true)
            {
                WhileBanner = true;
            }
            else
            {
                if (users[numUsers].name != "0")
                {
                    numUsers++;
                }
                else
                {
                    deleteAcc++;
                }
            }
        }
    }
    else
    {

        cout << "No se ha podido acceder a los datos, por favor contacte con el servicio de atencion al cliente";
    }

    fileRead.close();

    bool nameexist = false;

    do // para saber de que usuario tenemos que ver la evolucion y q ese usuario tenga q existir si o si
    {
        title();
        cout << "Introduce de nuevo tu nombre de usuario: ";
        cin >> nameTemp;

        for (int i = 0; i < numUsers + deleteAcc; i++)
        {

            if (nameTemp == users[i].name)
            {
                nameexist = true;
            }
        }

        if (nameexist == false)
        {
            cout << "Por favor, introduzca su nombre de usuario de manera correcta";
            system("cls");
        }

    } while (nameexist == false);

    system("cls");

    int elecc;

    char grafica[76][76];

    string file;

    file = nameTemp.append(".txt"); // funcion que añade algo al final de un string

    do
    {
        title();

        cout << "Que desea hacer, " << nameTemp << " ?: " << endl;
        cout << "1 - Ver mi evolucion" << endl;
        cout << "2 - Agregar peso" << endl;
        cout << "0 - Volver al menu" << endl;
        cin >> elecc;

        if (elecc == 1)
        {
            ifstream fileRead;

            fileRead.open(file);

            if (fileRead.is_open())
            {

                char show;

                while (fileRead.get(show)) // mientras lea algo lo muestra por pantalla
                {
                    cout << show;
                }

                cout << endl;
                system("pause");
                system("cls");
            }
            else
            {

                cout << "Aun no hay ningun historial suyo" << endl;
                Sleep(1000);
                system("cls");
            }

            fileRead.close();
        }
        else if (elecc == 2)
        {
            ifstream fileRead;

            fileRead.open(file);

            if (fileRead.is_open()) // si ya existe el fichero se lee
            {
                for (int i = 74; i >= 0; i--)
                {
                    for (int j = 0; j < 76; j++)
                    {
                        char caracter;

                        fileRead.get(caracter);

                        if (caracter == '\n')
                        {

                            j--; // Ignoramos los saltos de linea, decrementamos j para evitar que se sobrescriba con espacios en blanco
                        }
                        else
                        {
                            grafica[i][j] = caracter; // Si no es ninguno de los caracteres permitidos, usar espacio en blanco
                        }
                    }
                }
            }
            else // si no existe, llenamos el array con el eje X e Y y el resto en blanco
            {
                for (int i = 0; i < 76; i++)
                {
                    for (int j = 0; j < 76; j++)
                    {
                        if (j == 0) // Llenamos la columna 0 con 0, 75 a la mitad y 150 en el tope
                        {
                            if (i == 0)
                            {
                                grafica[i][j] = '0';
                            }
                            else if (i == 38)
                            {
                                grafica[i][j] = '-';
                            }
                            else if (i == 74)
                            {
                                grafica[i][j] = '-';
                            }
                            else
                            {
                                grafica[i][j] = ' ';
                            }
                        }
                        else if (j == 1) // La 1 la llenamos con "|""
                        {
                            grafica[i][j] = '|';
                        }
                        else if (i == 0)
                        {
                            grafica[i][j] = '_'; // Llenamos la fila 0 con "_"
                        }
                        else
                        {
                            grafica[i][j] = ' '; // Llenamos el resto con espacios en blanco
                        }
                    }
                }
            }

            fileRead.close();

            int i = 2;
            int j = 1;

            while (j < 76) // este bucle incrementa la i si encuentra un asterisco, si no lo encuentra finaliza el bucle y el valor de i nos indica la semana por la q va el usuario
            {
                if (grafica[j][i] == '*')
                {
                    i++;
                    j = 0;
                }
                j++;
            }

            int peso;

            do
            {
                cout << "Introduce tu peso (numero entero) de esta semana: " << endl;
                cout << "(maximo 148kg)" << endl;
                cin >> peso;

                if(peso < 2)
                {
                    cout << "El peso minimo es 2 kg" << endl;
                }
                else
                {
                    cout << "El peso maximo son 148 kg" << endl;
                }

            } while (peso < 2 || peso > 148);

            if (peso % 2 == 0) // el eje Y de la grafica va de 2 en 2 por eso se trata de manera diferente segun si es par o impar
            {
                peso = peso / 2;
            }
            else
            {
                peso = peso/2 + 1; // castea de manera automatica
            }

            grafica[peso][i] = '*';

            ofstream fileWrite(file); // escribimos el array con los datos nuevos en el fichero

            for (int i = 74; i >= 0; i--)
            {
                for (int j = 0; j < 76; j++)
                {
                    if (j == 75)
                    {
                        fileWrite << grafica[i][j] << endl;
                    }
                    else
                    {
                        fileWrite << grafica[i][j];
                    }
                }
            }

            fileWrite.close();

            cout << "Se ha generado una copia en el fichero: " << nameTemp << endl;
            system("pause");
            system("cls");
        }
        else if (elecc == 0)
        {
            cout << "Volviendo al menu..." << endl;
            Sleep(500);
            system("cls");
        }

    } while (elecc != 0);
}

/*
Pregunta el numero de dias y lo usa como variable de control para el bucle while. Por cada dia escribira en un txt 'rutina' siguiente una estructura determinada 
el numero del dia y su nombre, el nombre del siguiente ejercicio, el numero de series y repeticiones y el tiempo de descanso. Al acabar el while acaba la funcion.

-Entradas: none
-Salidas: none

*/

void routine()
{
    title();

    int days;

    cout << "Bienvenido al creador de rutinas de FESAC FITNESS APP, en este apartado de la aplicacion podra crear su propia" << endl;
    cout << "rutina de entrenamiento. Una vez la rutina se haya creado esta se encontrara en el fichero txt denominado 'rutina' lista para llevar en " << endl;
    cout << "su dispositivo movil o donde considere oportuno. Gracias por confiar en nosotros, vamos a crear su rutina!" << endl;
    cout << endl;

    system("pause");
    system("cls");

    do
    {
        title();

        cout << "Cuantos dias a la semana vas a entrenar?: ";
        cin >> days;
        cin.ignore();

        system("cls");

    } while (days > 7);

    int dayCont = 1;

    ofstream fileWrite;

    fileWrite.open("rutina.txt");

    while (days > 0)
    {
        title();

        char chose;

        cout << "Indica que va a entrenar el dia " << dayCont << ": ";
        string nameDay;
        getline(cin, nameDay);

        fileWrite << "==============================================================================" << endl;
        fileWrite << "\t\t\t"
                  << "Dia " << dayCont << ": " << nameDay << endl;
        fileWrite << "______________________________________________________________________________" << endl;

        do
        {
            cout << "Nombre del ejercicio: ";
            string temp;
            getline(cin, temp);

            fileWrite << temp << endl;

            cout << "Series x Repeticiones: ";
            getline(cin, temp);

            fileWrite << "\t"
                      << "Series:\t\t\t" << temp << endl;

            cout << "Tiempo de descanso: ";
            getline(cin, temp);

            fileWrite << "\t"
                      << "Descanso:\t\t" << temp << endl;
            fileWrite << "______________________________________________________________________________" << endl;

            cout << "Quiere agregar otro ejercicio?: s/n" << endl;
            cin >> chose;
            cin.ignore();

        } while (chose == 's' || chose == 'S');

        fileWrite << endl;

        days--;
        dayCont++;

        Sleep(500);
        system("cls");
    }

    fileWrite.close();

    title();

    cout << "Enhorabuena! Ha creado su rutina con exito, le recordamos que esta se encuentra en el fichero txt denominado 'rutina'. Hasta pronto!" << endl;

    system("pause");

    cout << "Volviendo al menu...";

    Sleep(1500);
    system("cls");
}