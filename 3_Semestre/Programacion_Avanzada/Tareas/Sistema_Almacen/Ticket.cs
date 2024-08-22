using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sistema_Almacen
{
    public partial class Ticket : Form
    {
        int ClientIndex = new int();
        DataTable TicketDataTable = new DataTable();

        public Ticket(int ClientIndex)
        {
            InitializeComponent();
            this.ClientIndex = ClientIndex;

            ProductsSearch.Show();
            ProductsSearch.DataSource = TicketDataTable;
        }

        private void Ticket_Load(object sender, EventArgs e)
        {
            TicketDataTable.Columns.Add("ID CODE", typeof(string));
            TicketDataTable.Columns.Add("Nombre de Producto", typeof(string));
            TicketDataTable.Columns.Add("Cantidad", typeof(int));

            foreach(var Producto in Variables.Lista_Clientes[ClientIndex].Ticket_Personal.ProductsList)
                TicketDataTable.Rows.Add(Variables.Lista_Productos[Producto.Index].ID_CODE, Variables.Lista_Productos[Producto.Index].Nombre_Producto, Producto.Quantity);

            QuantityText.Text += Variables.Lista_Clientes[ClientIndex].Ticket_Personal.contProductos.ToString();
        }
    }
}
