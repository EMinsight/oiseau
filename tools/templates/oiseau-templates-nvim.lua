-- Copyright (C) 2025 Tiago V. L. Amorim (@tiagovla)
--
-- This file is part of oiseau (https://github.com/tiagovla/oiseau)
--
-- SPDX-License-Identifier: GPL-3.0-or-later

local function get_script_dir()
    local info = debug.getinfo(1, "S")
    local path = info.source:sub(2)
    local dir = path:match "^(.*)[/\\]"
    local handle = io.popen("realpath " .. dir)
    if not handle then
        return nil
    else
        local abs_dir = handle:read "*l"
        handle:close()
        return abs_dir
    end
end

local function jump_inside_literal_braces()
    local total_lines = vim.api.nvim_buf_line_count(0)

    for row = 1, total_lines do
        local line = vim.api.nvim_buf_get_lines(0, row - 1, row, false)[1]
        local col = line:find "{}"
        if col then
            vim.api.nvim_win_set_cursor(0, { row, col + 1 })
            return
        end
    end
end

local script_dir = get_script_dir()
local group = vim.api.nvim_create_augroup("CppTemplates", { clear = true })
vim.api.nvim_create_autocmd({ "BufNewFile", "BufReadPost" }, {
    group = group,
    pattern = { "*.cpp", "*.hpp" },
    callback = function()
        if not (vim.fn.line "$" == 1 and vim.fn.getline(1) == "") then
            return
        end
        local filename = vim.fn.expand("%:t"):lower()
        local template_file = filename:match "test" and "test-new.cpp" or "new.cpp"
        local template_path = vim.fs.joinpath(script_dir, template_file)

        if vim.fn.filereadable(template_path) == 1 then
            vim.cmd("0r " .. vim.fn.fnameescape(template_path))
        end
        jump_inside_literal_braces()
    end,
})
