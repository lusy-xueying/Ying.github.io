USE [menu]
GO

/****** Object:  Table [dbo].[t_comment]    Script Date: 2020/7/1 14:01:58 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[t_comment](
	[id] [varchar](32) NOT NULL,
	[user_id] [varchar](32) NULL,
	[menu_id] [varchar](32) NULL,
	[comment] [varchar](1000) NULL,
	[lrsj] [varchar](50) NULL,
	[isdelete] [int] NULL,
 CONSTRAINT [PK_t_comment] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO

ALTER TABLE [dbo].[t_comment] ADD  CONSTRAINT [DF_t_comment_isdelete]  DEFAULT ((0)) FOR [isdelete]
GO

