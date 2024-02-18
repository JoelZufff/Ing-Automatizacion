namespace Sistema_Almacen
{
    partial class RegTicket
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle4 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle5 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle6 = new System.Windows.Forms.DataGridViewCellStyle();
            this.Title = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Quantity = new System.Windows.Forms.TextBox();
            this.AddButton = new System.Windows.Forms.Button();
            this.SendButton = new System.Windows.Forms.Button();
            this.Title2 = new System.Windows.Forms.Label();
            this.NameTitle = new System.Windows.Forms.Label();
            this.NameFilter = new System.Windows.Forms.TextBox();
            this.EraseButton = new System.Windows.Forms.Button();
            this.ProductsSearch = new System.Windows.Forms.DataGridView();
            this.ProductsTicket = new System.Windows.Forms.DataGridView();
            this.Filters = new System.Windows.Forms.Panel();
            this.panel1 = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.ProductsSearch)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.ProductsTicket)).BeginInit();
            this.Filters.SuspendLayout();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // Title
            // 
            this.Title.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.Title.AutoSize = true;
            this.Title.Font = new System.Drawing.Font("Franklin Gothic Medium Cond", 27.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Title.ForeColor = System.Drawing.Color.Black;
            this.Title.Location = new System.Drawing.Point(186, 9);
            this.Title.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.Title.Name = "Title";
            this.Title.Size = new System.Drawing.Size(292, 43);
            this.Title.TabIndex = 0;
            this.Title.Text = "LLENADO DE TICKET";
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(391, 12);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(81, 20);
            this.label3.TabIndex = 7;
            this.label3.Text = "Cantidad :";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Quantity
            // 
            this.Quantity.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.Quantity.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Quantity.Location = new System.Drawing.Point(476, 10);
            this.Quantity.Margin = new System.Windows.Forms.Padding(2);
            this.Quantity.Name = "Quantity";
            this.Quantity.Size = new System.Drawing.Size(41, 24);
            this.Quantity.TabIndex = 8;
            this.Quantity.Text = "1";
            // 
            // AddButton
            // 
            this.AddButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.AddButton.Location = new System.Drawing.Point(535, 10);
            this.AddButton.Margin = new System.Windows.Forms.Padding(2);
            this.AddButton.Name = "AddButton";
            this.AddButton.Size = new System.Drawing.Size(101, 24);
            this.AddButton.TabIndex = 9;
            this.AddButton.Text = "Agregar";
            this.AddButton.UseVisualStyleBackColor = true;
            this.AddButton.Click += new System.EventHandler(this.AddButton_Click);
            // 
            // SendButton
            // 
            this.SendButton.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.SendButton.Location = new System.Drawing.Point(247, 614);
            this.SendButton.Margin = new System.Windows.Forms.Padding(2);
            this.SendButton.Name = "SendButton";
            this.SendButton.Size = new System.Drawing.Size(188, 36);
            this.SendButton.TabIndex = 10;
            this.SendButton.Text = "Enviar Ticket";
            this.SendButton.UseVisualStyleBackColor = true;
            this.SendButton.Click += new System.EventHandler(this.SendButton_Click);
            // 
            // Title2
            // 
            this.Title2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.Title2.AutoSize = true;
            this.Title2.Font = new System.Drawing.Font("Franklin Gothic Medium Cond", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Title2.Location = new System.Drawing.Point(203, 2);
            this.Title2.Name = "Title2";
            this.Title2.Size = new System.Drawing.Size(240, 37);
            this.Title2.TabIndex = 11;
            this.Title2.Text = "Productos Agregados";
            // 
            // NameTitle
            // 
            this.NameTitle.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.NameTitle.AutoSize = true;
            this.NameTitle.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NameTitle.Location = new System.Drawing.Point(7, 12);
            this.NameTitle.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.NameTitle.Name = "NameTitle";
            this.NameTitle.Size = new System.Drawing.Size(69, 20);
            this.NameTitle.TabIndex = 12;
            this.NameTitle.Text = "Nombre:";
            // 
            // NameFilter
            // 
            this.NameFilter.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.NameFilter.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NameFilter.Location = new System.Drawing.Point(82, 10);
            this.NameFilter.Margin = new System.Windows.Forms.Padding(2);
            this.NameFilter.Name = "NameFilter";
            this.NameFilter.Size = new System.Drawing.Size(279, 24);
            this.NameFilter.TabIndex = 13;
            this.NameFilter.TextChanged += new System.EventHandler(this.NameFilter_TextChanged);
            // 
            // EraseButton
            // 
            this.EraseButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.EraseButton.Location = new System.Drawing.Point(528, 10);
            this.EraseButton.Margin = new System.Windows.Forms.Padding(2);
            this.EraseButton.Name = "EraseButton";
            this.EraseButton.Size = new System.Drawing.Size(101, 24);
            this.EraseButton.TabIndex = 14;
            this.EraseButton.Text = "Eliminar";
            this.EraseButton.UseVisualStyleBackColor = true;
            this.EraseButton.Click += new System.EventHandler(this.EraseButton_Click);
            // 
            // ProductsSearch
            // 
            this.ProductsSearch.AllowUserToAddRows = false;
            this.ProductsSearch.AllowUserToDeleteRows = false;
            this.ProductsSearch.AllowUserToResizeColumns = false;
            this.ProductsSearch.AllowUserToResizeRows = false;
            this.ProductsSearch.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.ProductsSearch.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.ProductsSearch.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.ProductsSearch.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.ProductsSearch.DefaultCellStyle = dataGridViewCellStyle2;
            this.ProductsSearch.Location = new System.Drawing.Point(23, 121);
            this.ProductsSearch.MultiSelect = false;
            this.ProductsSearch.Name = "ProductsSearch";
            this.ProductsSearch.ReadOnly = true;
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle3.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle3.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle3.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.ProductsSearch.RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
            this.ProductsSearch.RowHeadersVisible = false;
            this.ProductsSearch.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.ProductsSearch.ShowCellErrors = false;
            this.ProductsSearch.ShowCellToolTips = false;
            this.ProductsSearch.ShowEditingIcon = false;
            this.ProductsSearch.ShowRowErrors = false;
            this.ProductsSearch.Size = new System.Drawing.Size(625, 183);
            this.ProductsSearch.TabIndex = 15;
            this.ProductsSearch.Visible = false;
            // 
            // ProductsTicket
            // 
            this.ProductsTicket.AllowUserToAddRows = false;
            this.ProductsTicket.AllowUserToDeleteRows = false;
            this.ProductsTicket.AllowUserToResizeColumns = false;
            this.ProductsTicket.AllowUserToResizeRows = false;
            this.ProductsTicket.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.ProductsTicket.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            dataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle4.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle4.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle4.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle4.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle4.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.ProductsTicket.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle4;
            this.ProductsTicket.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridViewCellStyle5.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle5.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle5.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle5.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle5.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle5.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.ProductsTicket.DefaultCellStyle = dataGridViewCellStyle5;
            this.ProductsTicket.Location = new System.Drawing.Point(23, 370);
            this.ProductsTicket.MultiSelect = false;
            this.ProductsTicket.Name = "ProductsTicket";
            this.ProductsTicket.ReadOnly = true;
            dataGridViewCellStyle6.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle6.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle6.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle6.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle6.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle6.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.ProductsTicket.RowHeadersDefaultCellStyle = dataGridViewCellStyle6;
            this.ProductsTicket.RowHeadersVisible = false;
            this.ProductsTicket.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.ProductsTicket.ShowCellErrors = false;
            this.ProductsTicket.ShowCellToolTips = false;
            this.ProductsTicket.ShowEditingIcon = false;
            this.ProductsTicket.ShowRowErrors = false;
            this.ProductsTicket.Size = new System.Drawing.Size(625, 233);
            this.ProductsTicket.TabIndex = 16;
            this.ProductsTicket.Visible = false;
            // 
            // Filters
            // 
            this.Filters.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.Filters.Controls.Add(this.AddButton);
            this.Filters.Controls.Add(this.label3);
            this.Filters.Controls.Add(this.NameFilter);
            this.Filters.Controls.Add(this.Quantity);
            this.Filters.Controls.Add(this.NameTitle);
            this.Filters.Location = new System.Drawing.Point(12, 69);
            this.Filters.Name = "Filters";
            this.Filters.Size = new System.Drawing.Size(650, 46);
            this.Filters.TabIndex = 17;
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.Title2);
            this.panel1.Controls.Add(this.EraseButton);
            this.panel1.Location = new System.Drawing.Point(17, 314);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(650, 46);
            this.panel1.TabIndex = 18;
            // 
            // RegTicket
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.ClientSize = new System.Drawing.Size(674, 661);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.Filters);
            this.Controls.Add(this.ProductsTicket);
            this.Controls.Add(this.ProductsSearch);
            this.Controls.Add(this.SendButton);
            this.Controls.Add(this.Title);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MinimumSize = new System.Drawing.Size(690, 700);
            this.Name = "RegTicket";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Ticket";
            this.Load += new System.EventHandler(this.RegTicket_Load);
            ((System.ComponentModel.ISupportInitialize)(this.ProductsSearch)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.ProductsTicket)).EndInit();
            this.Filters.ResumeLayout(false);
            this.Filters.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label Title;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox Quantity;
        private System.Windows.Forms.Button AddButton;
        private System.Windows.Forms.Button SendButton;
        private System.Windows.Forms.Label Title2;
        private System.Windows.Forms.Label NameTitle;
        private System.Windows.Forms.TextBox NameFilter;
        private System.Windows.Forms.Button EraseButton;
        private System.Windows.Forms.DataGridView ProductsSearch;
        private System.Windows.Forms.DataGridView ProductsTicket;
        private System.Windows.Forms.Panel Filters;
        private System.Windows.Forms.Panel panel1;
    }
}