using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;

namespace Sistema_Almacen
{
    public static class Variables
    {
        public static string Admin_Password = "password";

        public static List<cliente> Lista_Clientes = new List<cliente>()
        {
            new cliente("Diego Joel Zuñiga Fragoso", "317684", "4423588044", "Ingenieria en Automatizacion", "Estudiante"),
            new cliente("Daniela del Carmen Manriquez Navarro", "307949", "4425249489", "Ingenieria en Automatizacion", "Estudiante")
        };

        public static List<producto> Lista_Productos = new List<producto>()
        {
            new producto("1", "Osciloscopio", 10),
            new producto("2", "Multimetro", 10),
            new producto("3", "Fuente de Voltaje", 10),
            new producto("4", "Potenciometro", 50),
            new producto("5", "Resistencia 200 Ohms", 100),
            new producto("6", "Resistencia 330 Ohms", 100),
            new producto("7", "Resistencia 1000 Ohms", 100),
            new producto("8", "Resistencia 2000 Ohms", 100)
        };
    }

    public class cliente
    {
        // Campos //
        public string nombre;
        public string expediente;
        public string celular;
        public string carrera;
        public string estatus;

        public ticket Ticket_Personal = new ticket();

        // Constructores y Destructores //
        public cliente() {}
        public cliente(string nombre, string expediente, string celular, string carrera, string estatus)
        {
            this.nombre = nombre;
            this.expediente = expediente;
            this.celular = celular;
            this.carrera = carrera;
            this.estatus = estatus;
        }
    }

    public class producto
    {
        // Campos //
        public string ID_CODE;
        public string Nombre_Producto;
        public int Cant_Total = 0;                     // Stock Total
        public int Cant_Prestamo = 0;                  // Cantidad en Prestamo
        public int Cant_Disp = 0;                      // Cant_Total - Cant_Prestamo


        // Constructores y Destructores //
        public producto() {}
        public producto(string ID_CODE, string Nombre_Producto, int Cant)
        {
            this.ID_CODE = ID_CODE;
            this.Nombre_Producto = Nombre_Producto;
            Cant_Total = Cant_Disp = Cant;
        }

        // Metodos //

        public void Loan(int Quantity, bool Add)
        {
            if(Add)
                Cant_Prestamo += Quantity;
            else
                Cant_Prestamo -= Quantity;

            Cant_Disp = Cant_Total - Cant_Prestamo;
        }
    }

    public class ticket
    {
        public class TicketProduct
        {
            public int Index;
            public int Quantity;

            public TicketProduct(int Index, int Quantity) { this.Index = Index;    this.Quantity = Quantity; }
        };

        // Campos //
        private string Fecha;
        public int contProductos = 0;					// Contador de productos en ticket
        public bool Enabled = false;                    // Si el ticket esta activo

        public List<TicketProduct> ProductsList = new List<TicketProduct>();

        // Metodos //
        public void Reset()
        {
            // Devolvemos stock de productos
            foreach (var Product in ProductsList)
                Variables.Lista_Productos[Product.Index].Loan(Product.Quantity, false);
                
            // Reseteamos las variables
            Fecha = string.Empty;
            contProductos = 0;
            Enabled = false;

            ProductsList.Clear();
        }

        public void AddProduct(int ProductIndex, int Quantity)
        {
            if(Fecha == string.Empty)
                Fecha = DateTime.Now.ToString();

            ProductsList.Add(new TicketProduct(ProductIndex,Quantity));

            Variables.Lista_Productos[ProductIndex].Loan(Quantity, true);
            contProductos++;

            Enabled = true;
        }
    }
}
