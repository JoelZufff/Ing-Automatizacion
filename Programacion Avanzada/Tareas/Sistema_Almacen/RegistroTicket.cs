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
    public partial class RegTicket : Form
    {
        int ClientIndex = new int();
        DataTable ProductsDataTable= new DataTable() , TicketDataTable = new DataTable();
        
        public RegTicket(int ClientIndex)
        {
            InitializeComponent();
            this.ClientIndex = ClientIndex;

            ProductsSearch.Show(); ProductsTicket.Show();
            ProductsSearch.DataSource = ProductsDataTable;
            ProductsTicket.DataSource = TicketDataTable;
        }
        
        private void RegTicket_Load(object sender, EventArgs e)
        {
            // Configuramos DataGridView
            ProductsDataTable.Columns.Add("ID CODE", typeof(string));
            ProductsDataTable.Columns.Add("Nombre de Producto", typeof(string));
            ProductsDataTable.Columns.Add("Cantidad Disponible", typeof(int));

            TicketDataTable.Columns.Add("ID CODE", typeof(string));
            TicketDataTable.Columns.Add("Nombre de Producto", typeof(string));
            TicketDataTable.Columns.Add("Cantidad", typeof(int));

            // Llenamos las filas del DataGridView de productos
            foreach (var Producto in Variables.Lista_Productos)
                ProductsDataTable.Rows.Add(Producto.ID_CODE, Producto.Nombre_Producto, Producto.Cant_Disp);
        }

        private void EraseButton_Click(object sender, EventArgs e)
        {
            if(TicketDataTable.Rows.Count == 0)
                return;
            
            DialogResult Answer = MessageBox.Show("¿Esta seguro que desea eliminar el elemento seleccionado?", "Confirmacion", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);
            if (Answer == DialogResult.No)
                return;

            // Eliminar producto de lista
            string ID = ProductsTicket.CurrentRow.Cells[0].Value.ToString();

            // Eliminamos producto en DataTable mostrado
            foreach (DataRow Row in TicketDataTable.Rows)
                if (Row[0].ToString() == ID) { Row.Delete(); break; }

        }

        private void SendButton_Click(object sender, EventArgs e)
        {
            foreach (DataRow row in TicketDataTable.Rows)
                foreach (var Producto in Variables.Lista_Productos)
                    if (Producto.ID_CODE.Contains(row["ID CODE"].ToString()))
                    {
                        // Agregamos producto al ticket personal del cliente
                        Variables.Lista_Clientes[ClientIndex].Ticket_Personal.AddProduct(Variables.Lista_Productos.IndexOf(Producto), int.Parse(row["Cantidad"].ToString()));
                        break;
                    }

            if (Variables.Lista_Clientes[ClientIndex].Ticket_Personal.Enabled)
            {
                MessageBox.Show("Ticket creado existosamente","Exito", MessageBoxButtons.OK, MessageBoxIcon.Information);
                this.Close();
            }
            else
                MessageBox.Show("Error, el ticket esta vacio","Error", MessageBoxButtons.OK,MessageBoxIcon.Error);
        }

        private void NameFilter_TextChanged(object sender, EventArgs e)
        {
            ProductsDataTable.Rows.Clear();
            
            if(NameFilter.Text == string.Empty)
                foreach (var Producto in Variables.Lista_Productos)
                    ProductsDataTable.Rows.Add(Producto.ID_CODE, Producto.Nombre_Producto, Producto.Cant_Disp);
            else
                foreach(var Producto in Variables.Lista_Productos)
                    if (Producto.Nombre_Producto.ToLower().Contains(NameFilter.Text.ToLower()))
                        ProductsDataTable.Rows.Add(Producto.ID_CODE, Producto.Nombre_Producto, Producto.Cant_Disp);
        }

        private void AddButton_Click(object sender, EventArgs e)
        {
            // Obtenemos ID de producto seleccionado
            string ID = ProductsSearch.CurrentRow.Cells[0].Value.ToString();

            // Ver si el producto no ha sido agregado ya, si es asi solo aumentar la cantidad

            // Buscamos producto en lista de productos
            foreach (var Producto in Variables.Lista_Productos)
                if(Producto.ID_CODE == ID)
                {
                    if((Producto.Cant_Disp - int.Parse(Quantity.Text)) < 0)     // Si no hay stock disponible
                    {
                        MessageBox.Show("No hay suficiente stock","Error",MessageBoxButtons.OK, MessageBoxIcon.Error);
                        break;
                    }
                    else        // Si hay stock disponible agregamos a datagridview de ticket
                    {
                        TicketDataTable.Rows.Add(Producto.ID_CODE, Producto.Nombre_Producto, int.Parse(Quantity.Text));
                        break;
                    }
                }
            NameFilter.Text = string.Empty;      Quantity.Text = "1";       // Reiniciamos filtros y cant
        }
    }
}
