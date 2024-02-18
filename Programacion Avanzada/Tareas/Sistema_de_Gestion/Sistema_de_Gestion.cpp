#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <conio.h>
#include <iomanip>

//+------------------------------------------------------------------+ 
//| Prototipos de Clases                                             | 
//+------------------------------------------------------------------+

class producto; class ticket; class cliente;

//+------------------------------------------------------------------+ 
//| Teclas Constantes                                                | 
//+------------------------------------------------------------------+

using namespace std;

#define ENTER 13
#define ESC 27
#define BORRAR 8
#define ADMIN '`'

//+------------------------------------------------------------------+ 
//| Variables para Listas                                            | 
//+------------------------------------------------------------------+

cliente*	inicioC = NULL, * finalC = NULL;		// Tendra la direccion del primer y ultimo cliente (Para lista)
producto*	inicioP = NULL, * finalP = NULL;		// Tendra la direccion del primer y ultimo producto (Ya fueron preinicializados arriba)
int			Cant_ProdStock;							// Productos en stock

//+------------------------------------------------------------------+ 
//| C L A S E S                                                      | 
//+------------------------------------------------------------------+

class producto										// Productos en lista
{
	public:

	string		ID_CODE;
	string		Nombre_Producto;
	int			Cant_Total = 0;						// Stock Total
	int			Cant_Prestamo = 0;					// Cantidad en Prestamo
	int			Cant_Disp = 0;						// Cant_Total - Cant_Prestamo

	producto*	Next = NULL;						// Tiene la direccion del siguiente producto en la lista

	bool		memodin;							// Bandera para evitar borrar memoria que no es de memoria dinamica

	producto() : memodin(true) {}

	producto(string ID, string Nombre, int Cant, bool memo)
	{
		ID_CODE = ID;
		Nombre_Producto = Nombre;
		Cant_Total = Cant_Disp = Cant;
		memo = memodin;

		if(Cant > 0)
			Cant_ProdStock++;

		// Actualizacion de lista de Productos

		if (inicioP == NULL) // Este es el primer Producto
		{
			inicioP = this;
			finalP = this;
		}
		else // Ya existe el primer Producto
		{
			finalP->Next = this;
			finalP = this;
		}

		Next = NULL;
	}

	// PENDIENTE: Hacer destructor que elimine el producto de la lista

	void Impresion(bool ADM)
	{
		cout << "\n\n\n\tNombre de Producto:\t" << this->Nombre_Producto;
		cout << "\n\tID CODE:\t" << this->ID_CODE;

		if (ADM)
		{
			cout << "\tInventario Total:\t" << this->Cant_Total;
			cout << "\tInventario en Prestamo:\t" << this->Cant_Prestamo;
		}
		else
			cout << "\tCantidad Disponible:\t" << this->Cant_Disp;
	}
};

class ticket										// Tickets por cliente. Cada cliente tendra un ticket
{
	public:

	string		Fecha;								// Establecer formato
	int			contProductos = 0;					// Contador de productos en ticket

	producto**	Productos = NULL;					// Arreglo de apuntadores a productos
	int*		CantidadProductos = NULL;			// Cantidad de unidades por cada producto

	ticket(int cant)
	{
		Productos = new producto * [cant];			// Arreglo de memoria dinamica de productos
		CantidadProductos = new int[cant];			// Arreglo de memoria dinamica de cant de productos

		contProductos = cant;						// Variable de cantidad de productos distintos
	}

	~ticket()
	{
		// Restablecemos inventario de productos
		for (int i = 0; i < contProductos; i++)
		{
			if (Productos[i]->Cant_Disp == 0)		// Si no habia stock, lo revertimos
				Cant_ProdStock++;

			Productos[i]->Cant_Prestamo -= CantidadProductos[i];
			Productos[i]->Cant_Disp = Productos[i]->Cant_Total - Productos[i]->Cant_Prestamo;
		}

		// Eliminamos Memoria Dinamica
		delete[] Productos;
		delete[] CantidadProductos;
	}

	void Impresion()
	{
		cout << "\n\n\tFecha de Prestamo:\t" << this->Fecha << endl << endl;

		cout << "\n" << setw(15) << "IDCODE";
		cout << "\t" << setw(40) << "NOMBRE";
		cout << "\t" << setw(10) << "CANTIDAD" << endl << endl;

		for (int i = 0; i < this->contProductos; i++)
		{
			cout << "\n" << setw(15) << this->Productos[i]->ID_CODE;
			cout << "\t" << setw(40) << this->Productos[i]->Nombre_Producto;
			cout << "\t" << setw(10) << this->CantidadProductos[i] << endl;
		}
	}
};

class cliente // Clientes en lista
{
	public:

	string Nombre;
	string Expediente;
	string Celular;
	string Carrera; // Lista Predefinida abajo
	string Estatus; // 1 = Estudiante . 2 = Profesor

	ticket* Ticket_Personal = NULL; // Solo se puede un ticket activo por cliente

	cliente* Next = NULL; // Tiene la direccion del siguiente cliente en la lista

	~cliente()
	{
		// Poner parte que elimine el cliente de la lista

		if (Ticket_Personal != NULL) // Hay un Ticket Personal
			delete Ticket_Personal;
	}

	void Impresion()
	{
		cout << "\n\n\tNombre:\t\t" << this->Nombre;
		cout << "\n\tExpediente:\t" << this->Expediente;
		cout << "\n\tCelular:\t" << this->Celular;
		cout << "\n\tCarrera:\t" << this->Carrera;
		cout << "\n\tEstatus:\t" << this->Estatus;
	}
};

//+------------------------------------------------------------------+ 
//| Productos Predefinidos                                           | 
//+------------------------------------------------------------------+

producto	A ("1", "Osciloscopio", 10, false);
producto	B ("2", "Multimetro", 10, false);
producto	C ("3", "Fuente de Voltaje", 10, false);
producto	D ("4", "Potenciometro", 50, false);
producto	E ("5", "Resistencia 200 Ohms", 100, false);
producto	F ("6", "Resistencia 330 Ohms", 100, false);
producto	G ("7", "Resistencia 1000 Ohms", 100, false);
producto	H ("8", "Resistencia 2000 Ohms", 100, false);

//+------------------------------------------------------------------+ 
//| Prototipos de Funcion                                            | 
//+------------------------------------------------------------------+

// Funciones para Menus
void MENU_ADMIN();
void MENU_CLIENTE();
// Funciones para cadenas
void CENTRAR(string);
void QUITESP(string&);
// Funciones para registro
void REGISTRO_CL(string);
void REGISTRO_P();
void REGISTRO_T();
bool MotorBusqueda(string &);

//+------------------------------------------------------------------+ 
//| Variables de configuracion inicial                               | 
//+------------------------------------------------------------------+

const int		NumCar = 13, NumEst = 2;

const string	Carreras[NumCar] = {"Ingenieria en Mecanica y Automotriz",
									"Ingenieria Fisica",
									"Ingenieria Agroindustrial",
									"Ingenieria Civil",
									"Ingenieria Industrial y Manufactura",
									"Ingenieria Electromecanica",
									"Ingenieria en Automatizacion",
									"Ingenieria en Nanotecnologia",
									"Ingenieria Biomedica",
									"Licenciatura en Matematicas Aplicadas",
									"Licenciatura en Diseno Industrial",
									"Licenciatura en Arquitectura",
									"Licenciatura en Animacion Digital" };

const string	Estatus[NumEst] = { "Estudiante", "Profesor" };
const char		Numeros[] = { '0','1','2','3','4','5','6','7','8','9' };

//+------------------------------------------------------------------+ 
//| Variables Auxiliares                                             | 
//+------------------------------------------------------------------+

cliente*		auxCliente = NULL;
producto*		auxProducto = NULL;
int				Op;

void main()
{
	cliente*	erase = NULL;
	producto*	erase2 = NULL;

MENUPRIN:
	system("cls");
	CENTRAR("B  I  E  N  V  E  N  I  D  O");
	cout << "\n\n\n\tPresione ENTER para comenzar, o ESC para salir";

	do
	{
		Op = _getch();
	} while ((Op != ENTER) && (Op != ADMIN) && (Op != ESC));


	if (Op == ENTER)							// Menu para clientes
	{
		MENU_CLIENTE();
		goto MENUPRIN;
	}
	else if (Op == ADMIN)						// Menu para adminsitradores
	{
		MENU_ADMIN();
		goto MENUPRIN;
	}
	else {}										// ESC no hacemos nada

	// Liberamos memoria reservada

	auxCliente = inicioC;

	while (auxCliente != NULL)
	{
		erase = auxCliente;
		auxCliente = auxCliente->Next;

		delete erase;
	}

	auxProducto = inicioP;

	while (auxProducto != NULL)
	{
		erase2 = auxProducto;
		auxProducto = auxProducto->Next;

		if (erase2->memodin)					// Si fue creado por memoria dinamica
			delete erase2;
	}
}

void MENU_CLIENTE()
{
	string		exp;

	system("cls");
	CENTRAR("L A B O R A T O R I O  D E  A U T O M A T I Z A C I O N");

	cout << "\n\n\n\tIngrese su numero de Expediente:\t";
	getline(cin, exp);
	QUITESP(exp);

	auxCliente = inicioC;

	// Revisamos la lista de clientes registrados en caso de una coincidencia en el Expediente
	while (auxCliente != NULL)
	{
		if (auxCliente->Expediente == exp)
			break;

		auxCliente = auxCliente->Next;
	}

	if (auxCliente == NULL)								// No existen coincidencias
	{
		cout << "\n\n\tEste numero de Expediente no ha sido registrado";
		REGISTRO_CL(exp);
	}
	else												// Si existe el cliente
	{
		system("cls");
		CENTRAR("I N T E R F A Z  D E  C L I E N T E");
		cout << "\n\n\tBIENVENIDO, estos son sus datos:";

		auxCliente->Impresion();

		if (auxCliente->Ticket_Personal != NULL)		// Si el TICKET esta activo
		{
			cout << endl << endl;

			CENTRAR("Usted ya cuenta con un ticket ACTIVO");
			cout << endl;

			// Se imprime el ticket

			auxCliente->Ticket_Personal->Impresion();

			cout << endl << endl << "\tSi desea abrir otro ticket, cierre ticket anterior con un administrador";
			system("pause>nul");
		}
		else if (auxCliente->Ticket_Personal == NULL)	// No existe el TICKET
		{
			if (Cant_ProdStock == 0)					// Si no hay productos con stock en el almacen
			{
				cout << endl << endl;
				CENTRAR("YA NO HAY PRODUCTOS EN EL ALMACEN, VUELVA PRONTO");
			}
			else										// Si hay productos con stock en el almacen
			{
				REGISTRO_T();
			}
			system("pause>nul");
		}
	}
}

void MENU_ADMIN()
{
	int			cont;
	string		exp;

MENUADM:
	system("cls");

	CENTRAR("M O D O  A D M I N I S T R A D O R");
	cout << "\n\n\n\t\t1. Administracion de Clientes\n\n\t\t2. Administracion de Productos\n\n\t\t3. Administracion de Tickets\n\n\t\t4. Volver a modo cliente\n\n\n";
	cout << "\n\tPresione el numero de tecla de la opcion a elegir";

	do
	{
		Op = _getch();
	} while ((Op != '1') && (Op != '2') && (Op != '3') && (Op != '4'));

	if (Op == '1')									// Administracion de Clientes
	{
	MENUCLI:
		system("cls");
		CENTRAR("A D M I N I S T R A C I O N  D E  C L I E N T E S");

		cout << "\n\n\n\t\t1. Registro de Cliente\n\n\t\t2. Lista de Clientes\n\n\t\t3. Volver al menu anterior\n\n\n";
		cout << "\n\tPresione el numero de tecla de la opcion a elegir";

		do
		{
			Op = _getch();
		} while ((Op != '1') && (Op != '2') && (Op != '3'));

		if (Op == '1')								// Registro de Cliente
		{
			system("cls");
			REGISTRO_CL("");
			goto MENUCLI;
		}
		else if (Op == '2')							// Lista de Clientes
		{
			system("cls");

			if (inicioC == NULL)					// Aun no hay clientes
			{
				cout << endl << endl << endl;
				CENTRAR("N O  H A Y  C L I E N T E S  R E G I S T R A D O S");
			}
			else
			{
				CENTRAR("L I S T A  D E  C L I E N T E S");
				auxCliente = inicioC;

				while (auxCliente != NULL)			// Mientras el "Next" exista
				{
					auxCliente->Impresion();
					auxCliente = auxCliente->Next;
				}
			}
			system("pause>nul");
			goto MENUCLI;
		}

		goto MENUADM;
	}
	else if (Op == '2')								// Administracion de Productos
	{
	MENUPROD:
		system("cls");
		CENTRAR("A D M I N I S T R A C I O N  D E  P R O D U C T O S");

		cout << "\n\n\n\t\t1. Registro de Producto\n\n\t\t2. Lista de Productos\n\n\t\t3. Volver al menu anterior\n\n\n";
		cout << "\n\tPresione el numero de tecla de la opcion a elegir";

		do
		{
			Op = _getch();
		} while ((Op != '1') && (Op != '2') && (Op != '3'));

		if (Op == '1')								// Registro de Productos
		{
			system("cls");
			REGISTRO_P();
			goto MENUPROD;
		}
		else if (Op == '2')							// Lista de Productos
		{
			system("cls");

			if (inicioP == NULL)					// Aun no hay productos
			{
				cout << endl << endl << endl;
				CENTRAR("N O  H A Y  P R O D U C T O S  R E G I S T R A D O S");
			}
			else
			{
				CENTRAR("L I S T A  D E  P R O D U C T O S");
				auxProducto = inicioP;

				do
				{
					auxProducto->Impresion(true);
					auxProducto = auxProducto->Next;
				} while (auxProducto != NULL);		// Mientras el "Next" exista
			}
			system("pause>nul");
			goto MENUPROD;
		}

		goto MENUADM;
	}
	else if (Op == '3')								// Administracion de Tickets
	{
	MENUTICK:
		system("cls");
		CENTRAR("A D M I N I S T R A C I O N  D E  T I C K E T S");

		cout << "\n\n\n\t\t1. Tickets Activos\n\n\t\t2. Buscar y eliminar Ticket\n\n\t\t3. Volver al menu anterior\n\n\n";
		cout << "\n\tPresione el numero de tecla de la opcion a elegir";

		do
		{
			Op = _getch();
		} while ((Op != '1') && (Op != '2') && (Op != '3'));

		if (Op == '1')								// Tickets Activos
		{
			system("cls");
			CENTRAR("T I C K E T S  A C T I V O S");
			cout << endl << endl;

			// Imprimir Todos los tickets

			cont = 0;								// Contador de tickets
			auxCliente = inicioC;

			while (auxCliente != NULL)
			{
				if (auxCliente->Ticket_Personal != NULL) // Si el cliente tiene ticket activo
				{
					cout << endl << endl << "\tNombre:\t" << auxCliente->Nombre << "\t Expediente:\t" << auxCliente->Expediente;
					auxCliente->Ticket_Personal->Impresion();
					cout << endl << "\t--------------------------------------------------------------------------------------------------";
					cont++;
				}

				auxCliente = auxCliente->Next;
			}

			if (cont == 0)
			{
				system("cls");
				cout << endl << endl;
				CENTRAR("N O  H A Y  T I C K E T S  A C T I V O S");
			}

			system("pause>nul");

			goto MENUTICK;
		}
		else if (Op == '2') // Buscar Ticket
		{
		Busqueda:
			system("cls");
			cout << "\n\n\tSi desea buscar un ticket presione ENTER, de lo contrario presione ESC para salir";

			do
			{
				Op = _getch();
			} while ((Op != ENTER) && (Op != ESC));


			if (Op == ENTER) // Buscar y eliminar ticket 
			{
				system("cls");
				CENTRAR("B U S Q U E D A  D E  T I C K E T S  A C T I V O S");

				cout << "\n\n\tIngrese su numero de Expediente:\t";
				getline(cin, exp);
				QUITESP(exp);

				auxCliente = inicioC;
				//Buscamos si hay un ticket con el expediente solicitado 
				while (auxCliente != NULL)
				{
					if (auxCliente->Expediente == exp)
						break;

					auxCliente = auxCliente->Next;
				}

				if (auxCliente == NULL) // No existe el expediente
				{
					cout << "\n\n\tEl numero de Expediente no existe, intentelo de nuevo";
					system("pause>nul");
					goto Busqueda;
				}
				else // Si existe el Expediente
				{
					if (auxCliente->Ticket_Personal == NULL)
					{
						cout << endl << endl;
						CENTRAR("ESTE NUMERO DE EXPEDIENTE NO TIENE TICKET ACTIVO");
						system("pause>nul");
						goto Busqueda;
					}
					else
					{
						cout << "\n\tHay un ticket activo:";
						auxCliente->Ticket_Personal->Impresion();

						cout << "\n\n\n\tSi desea cerrar el ticket presione ENTER, de lo contrario presione ESC para salir";

						do
						{
							Op = _getch();
						} while ((Op != ENTER) && (Op != ESC));

						if (Op == ENTER)
						{
							// Eliminamos Ticket Personal

							delete auxCliente->Ticket_Personal;
							auxCliente->Ticket_Personal = NULL;

							cout << endl << endl;
							CENTRAR("El ticket fue eliminado existosamente");
						}
						else {}
					}
				}
			}

			goto MENUTICK;
		}

		goto MENUADM;
	}
}

void CENTRAR(string A)
{
	int i;

	for (i = 0; i < (60 - A.length() / 2); i++)
		cout << " ";
	cout << A;
}

void QUITESP(string& A)
{
	int i, j, final = A.size();

	for (i = 0; i < final; i++)
	{
		if (A[i] == ' ') // Ve si el caracter de la posicion [i] es un espacio
		{
			// Recorremos todo 1 caracter (i-- es para no avanzar en el for de afuera)
			for (j = i--; j < final - 1; j++)
				A[j] = A[j + 1];
			A.resize(--final);
		}
	}
}

void REGISTRO_CL(string exp)
{
	int i, j, contnum;

	cout << "\n\n\tPresione ENTER para comenzar REGISTRO, de lo contrario presione ESC para cancelar";

	do {
		Op = _getch();
	} while ((Op != ESC) && (Op != ENTER));

	if (Op == ENTER)
	{
		cliente* Nuevo = new cliente;

		if (Nuevo == NULL)
			cout << "\n\tERROR, MEMORIA INSUFICIENTE";
		else
		{
			// Recoleccion de datos

		Nombre:

			system("cls");
			CENTRAR("R E G I S T R O  D E  N U E V O  C L I E N T E");

			cout << "\n\n\n\tNombre Completo:\t\t";
			getline(cin, Nuevo->Nombre);

			if (Nuevo->Nombre.length() == 0) // Comprobacion de que no este vacio
			{
				cout << "\n\t\tNo es valido, intentelo de nuevo";
				system("pause>nul");
				goto Nombre;
			}

			cout << "\n\n\tEl nombre almacenado es: " << Nuevo->Nombre << "\n\n\tSi desea cambiarlo presione ESC, de lo contrario presione cualquier tecla para continuar";
			Op = _getch();

			if (Op == ESC) // El cliente desea cambiar su nombre
				goto Nombre;

		Expediente:
			system("cls");
			CENTRAR("R E G I S T R O  D E  N U E V O  C L I E N T E");

			cout << "\n\n\n\tNumero de Expediente:\t\t";

			if (exp.length() == 0) // El expediente recibido esta vacio
			{
				getline(cin, Nuevo->Expediente);
				QUITESP(Nuevo->Expediente);
			}
			else // Ya se recibio expediente
			{
				Nuevo->Expediente = exp;
				cout << Nuevo->Expediente << endl;
			}

			contnum = 0; // Contador de numeros
			for (i = 0; i < Nuevo->Expediente.length(); i++)
			{
				for (j = 0; j < 10; j++) // Comparar con caracteres numeros
					if (Nuevo->Expediente[i] == Numeros[j])
						contnum++;
			}

			// Comprobacion sobre si no ha sido registrado el expediente anteriormente

			if (contnum == Nuevo->Expediente.length()) // Si el exp es valido
			{
				auxCliente = inicioC;

				// Revisamos la lista de clientes registrados en caso de una coincidencia en el Expediente
				while (auxCliente != NULL)
				{
					if (auxCliente->Expediente == Nuevo->Expediente)
						break;

					auxCliente = auxCliente->Next;
				}
			}

			if ((Nuevo->Expediente.length() == 0) || (auxCliente != NULL) || (contnum != Nuevo->Expediente.length())) // Comprobacion de que no este vacio o no haya sido registrado antes
			{
				cout << "\n\t\tYa fue registrado o no es valido, intentelo de nuevo";
				system("pause>nul");
				exp = "";
				goto Expediente;
			}

			cout << "\n\n\tEl expediente almacenado es:\t" << Nuevo->Expediente << "\n\n\tSi desea cambiarlo presione ESC, de lo contrario presione cualquier tecla para continuar";
			Op = _getch();

			if (Op == ESC)
			{
				exp = ""; // Para no volver a mandar el mismo expediente, si se mando uno
				goto Expediente;
			}

		Celular:
			system("cls");
			CENTRAR("R E G I S T R O  D E  N U E V O  C L I E N T E");

			cout << "\n\n\n\tNumero de Celular (10 digitos):\t\t";
			getline(cin, Nuevo->Celular);
			QUITESP(Nuevo->Celular);

			// Comprobacion de que los caracteres sean numeros
			contnum = 0; // Contador de numeros
			for (i = 0; i < Nuevo->Celular.length(); i++)
			{
				for (j = 0; j < 10; j++) // Comparar con caracteres numeros
					if (Nuevo->Celular[i] == Numeros[j])
						contnum++;
			}

			if ((Nuevo->Celular.length() == 0) || (contnum != 10) || (contnum < Nuevo->Celular.length())) // Numero invalido. Esta vacio o no son todos numeros o no son 10 numeros
			{
				cout << "\n\t\tNo es valido, intentelo de nuevo";
				system("pause>nul");
				goto Celular;
			}

			cout << "\n\n\tEl numero almacenado es: " << Nuevo->Celular << "\n\n\tSi desea cambiarlo presione ESC, de lo contrario presione cualquier tecla para continuar";
			Op = _getch();

			if (Op == ESC)
				goto Celular;

		Carrera:
			system("cls");
			CENTRAR("R E G I S T R O  D E  N U E V O  C L I E N T E");

			cout << endl << endl << endl;
			for (i = 0; i < NumCar; i++)
				cout << "\t" << i + 1 << ".\t" << Carreras[i] << endl << endl;

			cout << "\n\tIngrese el numero de su carrera:\t";
			cin >> Op;
			
			if (!cin.good()) // Si hay error en cin limpia el BUFFER
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			if (Op <= 0 || Op > NumCar) // Si no es valida la opcion
				goto Carrera;
				

			Nuevo->Carrera = Carreras[--Op];

			cout << "\n\n\tLa carrera almacenada es: " << Nuevo->Carrera << "\n\n\tSi desea cambiarla presione ESC, de lo contrario presione cualquier tecla para continuar";
			Op = _getch();

			if (Op == ESC)
				goto Carrera;

		Estatus:
			system("cls");
			CENTRAR("R E G I S T R O  D E  N U E V O  C L I E N T E");

			cout << endl << endl << endl;
			for (int i = 0; i < NumEst; i++)
				cout << "\t" << i + 1 << ".\t" << Estatus[i] << endl << endl;

			cout << "\n\tPresione el numero de su Estatus:\t";
			do
			{
				Op = _getch();
			} while ((Op < 49) || (Op > 48 + NumEst));
			Op -= 49;
			Nuevo->Estatus = Estatus[Op];
			cout << Nuevo->Estatus;

			cout << "\n\n\tSi desea cambiarlo presione ESC, de lo contrario presione cualquier tecla para continuar";
			Op = _getch();

			if (Op == ESC)
				goto Estatus;

			// Actualizacion de lista de Clientes

			if (inicioC == NULL) // Este es el primer cliente
			{
				inicioC = Nuevo;
				finalC = Nuevo;
			}
			else // Ya existe el primer cliente
			{
				// Agregamos "Nuevo" a la lista de Clientes

				finalC->Next = Nuevo;
				finalC = Nuevo;
			}
		}

		cout << endl << endl << endl;
		CENTRAR("REGISTRO EXITOSO, presione cualquier tecla para continuar");

		_getch();

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	else {} // Presiono ESC
}

void REGISTRO_P()
{
	int i, j;

	cout << "\n\n\tPresione ENTER para comenzar REGISTRO, de lo contrario presione ESC para cancelar";

	do
	{
		Op = _getch();
	} while ((Op != ESC) && (Op != ENTER));

	if (Op == ENTER)
	{
		producto* Nuevo = new producto;

		if (Nuevo == NULL)
			cout << "\n\tERROR, MEMORIA INSUFICIENTE";
		else
		{
			// Recoleccion de datos
		IDCODE:

			system("cls");
			CENTRAR("R E G I S T R O  D E  N U E V O  P R O D U C T O");

			cout << "\n\n\n\tID CODE:\t\t";
			getline(cin, Nuevo->ID_CODE);
			QUITESP(Nuevo->ID_CODE);

			int contnum = 0; // Contador de numeros
			for (i = 0; i < Nuevo->ID_CODE.length(); i++)
			{
				for (j = 0; j < 10; j++) // Comparar con caracteres numeros
					if (Nuevo->ID_CODE[i] == Numeros[j])
						contnum++;
			}
			
			// Comprobacion sobre si no ha sido registrado el ID_CODE anteriormente
			auxProducto = inicioP;

			while (auxProducto != NULL) // Revisamos la lista de productos registrados en caso de una coincidencia en el ID_CODE
			{
				if (auxProducto->ID_CODE == Nuevo->ID_CODE)
					break;

				auxProducto = auxProducto->Next;
			}

			if ((Nuevo->ID_CODE.length() == 0) || (contnum != Nuevo->ID_CODE.length()) || (auxProducto != NULL)) // No todos los caracteres son numeros o ya existe IDCODE
			{
				cout << "\n\t\tNo es valido o ya existe el ID_CODE, intentelo de nuevo";
				cout << "\t* = " << (auxProducto == NULL);
				system("pause>nul");
				goto IDCODE;
			}

			cout << "\n\n\tEl ID_CODE almacenado es: " << Nuevo->ID_CODE << "\n\n\tSi desea cambiarlo presione ESC, de lo contrario presione cualquier tecla para continuar";
			Op = _getch();

			if (Op == ESC)
				goto IDCODE;

		NombreProd:

			system("cls");
			CENTRAR("R E G I S T R O  D E  N U E V O  P R O D U C T O");

			cout << "\n\n\n\tNombre del Producto:\t";
			getline(cin, Nuevo->Nombre_Producto);

			if (Nuevo->Nombre_Producto.length() == 0) // Comprobacion de que no este vacio
			{
				cout << "\n\t\tNo es valido, intentelo de nuevo";
				system("pause>nul");
				goto NombreProd;
			}

			cout << "\n\n\tEl nombre almacenado es: " << Nuevo->Nombre_Producto << "\n\n\tSi desea cambiarlo presione ESC, de lo contrario presione cualquier tecla para continuar";
			Op = _getch();

			if (Op == ESC)
				goto NombreProd;

		Stock:

			system("cls");
			CENTRAR("R E G I S T R O  D E  N U E V O  P R O D U C T O");

			cout << "\n\n\n\tStock Inicial:\t\t";

			cin >> Nuevo->Cant_Total;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer para evitar omitir getline

			if (Nuevo->Cant_Total < 0) // Comprobacion de no sea negativo el producto
			{
				cout << "\n\t\tNo es valido, intentelo de nuevo";
				system("pause>nul");
				goto Stock;
			}

			cout << "\n\n\tEl stock almacenado es: " << Nuevo->Cant_Total << "\n\n\tSi desea cambiarlo presione ESC, de lo contrario presione cualquier tecla para continuar";
			Op = _getch();

			if (Op == ESC)
				goto NombreProd;

			// Establecer variables de inventario

			Nuevo->Cant_Disp = Nuevo->Cant_Total;

			if (Nuevo->Cant_Total > 0) // Actualizamos el contador de productos con stock
				Cant_ProdStock ++;

			// Actualizacion de lista de Productos

			if (inicioP == NULL) // Este es el primer Producto
			{
				inicioP = Nuevo;
				finalP = Nuevo;
			}
			else // Ya existe el primer Producto
			{
				finalP->Next = Nuevo;
				finalP = Nuevo;
			}


		}

		cout << endl << endl << endl;
		CENTRAR("REGISTRO EXITOSO, presione cualquier tecla para continuar");
		system("pause>nul");
	}
	else {} // Presiono ESC
}

void REGISTRO_T()
{
	int i, j, k, cant, cont;
	string IDCODE, Busqueda;

	TICKETR:

	cout << "\n\n\n\tSi desea abrir un ticket presione ENTER, de lo contrario presione ESC para salir";

	cin.clear();

	do
	{
		Op = _getch();
	} while ((Op != ENTER) && (Op != ESC));


	if (Op == ENTER) // Menu para clientes
	{
		do
		{
			system("cls");
			CENTRAR("R E G I S T R O  D E  T I C K E T");

			cout << "\n\n\n\tProductos distintos disponibles: \t" << Cant_ProdStock << endl;
			cout << "\n\n\tIngrese la cantidad de productos distintos que requiere:\t";
			cin >> cant;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (cant <= 0 || cant > Cant_ProdStock);

		auxCliente->Ticket_Personal = new ticket (cant);

		vector<producto*> Lista; // Vector de memoria dinamica

		for (i = 0; i < cant; i++) // Ingresamos producto por producto
		{
			Busqueda.clear(); // Limpiamos texto de busqueda

		INGRESOPROD:

			do
			{
				Lista.clear(); // Reiniciamos lista de coincidencias

				system("cls");
				CENTRAR("R E G I S T R O  D E  T I C K E T");

				cout << "\n\n\n\tNOTA: Cuando solo haya un producto presione ENTER para guardarlo";

				cout << "\n\n\tIngrese el nombre del producto:\t\t" << Busqueda;

				if (Busqueda.length() > 0) // Si ya hay una busqueda
				{
					auxProducto = inicioP;

					while (auxProducto != NULL)
					{
						// Buscamos coincidencia entre el nombre y la busqueda

						bool flag = false;

						if (Busqueda.length() <= auxProducto->Nombre_Producto.length()) // Si el tamaño de la busqueda es menor o igual que el nombre del producto
						{
							// j (Posicion de nombre), k (Posicion de busqueda), cont (Contador de coincidencias)

							for (j = 0, k = 0, cont = 0; j < auxProducto->Nombre_Producto.length() && k < Busqueda.length(); j++, flag ? k++:k) // Caracter por caracter PENDIENTE REVISAR CUANDO APLICA
							{
								if (tolower(Busqueda[k]) == tolower(auxProducto->Nombre_Producto[j])) // Si son la misma letra
								{
									flag = true;
									cont++;
								}
							}
						}
						else
							cont = 0; // Para evitar que pase un producto que no debe

						// Ver si le agrego funcion para buscar tambien por IDCODE

						// Si hay coincidencia guardamos su direccion al arreglo de Lista
						if (cont == Busqueda.length())
							Lista.push_back(auxProducto); // Agregamos el producto a la lista de coincidencias

						auxProducto = auxProducto->Next;
					}

					// Imprimimos lista de coincidencias

					for (j = 0; j < Lista.size(); j++)
					{
						Lista[j]->Impresion(false);
						cout << endl << endl << "\t--------------------------------------------------------------------------------------------------";
					}
				}
			}
			while (MotorBusqueda(Busqueda));

			if(Lista.size() == 1) // Solo hay un elemento
			{
				// Revisamos la lista de productos anteriores registrados en caso de una coincidencia

				for (j = 0; j < i; j++)
				{
					if (auxCliente->Ticket_Personal->Productos[j] == Lista[0])
					{
						cout << endl << endl << endl;
						CENTRAR("EL PRODUCTO YA FUE INGRESADO, VUELVALO A INTENTAR");
						system("pause>nul");
						goto INGRESOPROD;
					}
				}

				auxCliente->Ticket_Personal->Productos[i] = Lista[0];

				cout << "\n\n\n\tIngrese la cantidad que desea:\t";

				// Guardamos la cantidad de ese producto en la lista del ticket, en la posicion del producto actual
				cin >> auxCliente->Ticket_Personal->CantidadProductos[i];

				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				// Ver si la cantidad de producto solicitado es mayor a la disponible o es menor que 0
				while ((auxCliente->Ticket_Personal->CantidadProductos[i] > auxCliente->Ticket_Personal->Productos[i]->Cant_Disp) ||
					(auxCliente->Ticket_Personal->CantidadProductos[i] <= 0))
				{
					cout << "\n\n\tCantidad INVALIDA\n\n\tIngrese la cantidad que desea:\t";
					cin >> auxCliente->Ticket_Personal->CantidadProductos[i];

					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				// Actualizamos Inventario (Cantidad Disponible y Cantidad Prestamo)
				auxCliente->Ticket_Personal->Productos[i]->Cant_Prestamo += auxCliente->Ticket_Personal->CantidadProductos[i];
				auxCliente->Ticket_Personal->Productos[i]->Cant_Disp = auxCliente->Ticket_Personal->Productos[i]->Cant_Total - auxCliente->Ticket_Personal->Productos[i]->Cant_Prestamo;

				if (auxCliente->Ticket_Personal->Productos[i]->Cant_Disp == 0) // Si se quedo sin stock
					Cant_ProdStock--;

				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer para evitar omitir getline
			}
			else
			{
				cout << endl << endl << endl;
				CENTRAR("NO SE CONCRETO LA BUSQUEDA, VUELVALO A INTENTAR");
				system("pause>nul");

				goto INGRESOPROD;
			}
		}

		// Se temino de llenar el ticket, Mostramos TICKET Final

		system("cls");
		CENTRAR("C O N F I R M A C I O N  D E  T I C K E T");

		// Guardamos fecha automaticamente, con fecha de computadora
		auxCliente->Ticket_Personal->Fecha = __DATE__;

		auxCliente->Ticket_Personal->Impresion();
		cout << "\n\n\n\tSi desea reiniciar el ticket presione ESC, de lo contrario presione ENTER para confirmar";

		do
		{
			Op = _getch();
		} 
		while ((Op != ENTER) && (Op != ESC));

		if (Op == ESC) // Eliminamos Ticket Personal
		{
			delete auxCliente->Ticket_Personal;
			auxCliente->Ticket_Personal = NULL;
			goto TICKETR;
		}
		else
		{
			cout << endl << endl << endl;
			CENTRAR("TICKET ACTIVADO EXITOSAMENTE, VUELVA PRONTO");
		}
	}
	else {} // ESC no hacemos nada
}

bool MotorBusqueda(string& Busqueda)
{
	Busqueda:
	char Buffer;

	Buffer = _getch();

	// Si es un caracter o numero
	if ((Buffer >= 'A' && Buffer <= 'Z') || (Buffer >= 'a' && Buffer <= 'z') || (Buffer >= '0' && Buffer <= '9')) 
		Busqueda += Buffer;
	else if (Buffer == 32) // Si es un espacio
		Busqueda += ' ';
	else if ((Buffer == BORRAR) && (Busqueda.length() > 0))
		Busqueda.resize(Busqueda.size() - 1); // Eliminamos el ultimo caracter
	else if (Buffer == ENTER)
		return false;
	else
		goto Busqueda;

	return true;
}




// IMPLEMENTAR VECTOR PARA LA LISTA DE PRODUCTOS DE PRODUCTO EN TICKET CLIENTE Y PREGUNTAR DESPUES DE CADA PRODUCTO SI DESEA SEGUIR INGRESANDO
// PONER MOTOR DE BUSQUEDA DE PRODUCTOS CON IDCODE TAMBIEN
// VER SI IMPLEMENTO IS DIGIT PARA COMPROBAR DIGITOS
// VER SI ACTIVO EL MOTOR DE BUSQUEDA PARA LA BUSQUEDA DE CLIENTES
// Si dos productos se llaman igual, habra problema con motor de busqueda