USE [menu]
GO

/****** Object:  Table [dbo].[t_cart]    Script Date: 2020/7/1 14:00:14 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[t_cart](
	[id] [varchar](32) NOT NULL,
	[user_id] [varchar](32) NULL,
	[menu_id] [varchar](32) NULL,
	[lrsj] [varchar](50) NULL,
 CONSTRAINT [PK_t_cart] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO


