#pragma once

#include <Windows.h>
#define STB_IMAGE_IMPLEMENTATION

#include <Settings/Sakura.hpp>

#include <Render/imgui/stb_image.h>
#include <Render/imgui/imgui.h>
#include <Render/imgui/imgui_impl_dx11.h>
#include <Render/imgui/imgui_impl_win32.h>
#include <Render/imgui/imgui_internal.h>

#include <Render/font/FA6PRO.h>
#include <Render/font/Regular.h>
#include <Render/font/Icons.h>
#include <Render/images/logo.h>

#include <Functions/Extractor.hpp>

#include <d3d11.h>

#define STRING_T(x) std::string(x).c_str()

enum EMenuCategory {
	EMC_Visual = 0x0,
	EMC_Misc = 0x1,
	EMC_Player = 0x2,
	EMC_Advance = 0x3,
	EMC_Options = 0x4,
	EMC_Main = 0xFFFFFFFF,
};

class CMenu {
public:
    bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
    {
        // Load from disk into a raw RGBA buffer
        int image_width = 0;
        int image_height = 0;
        unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
        if (image_data == NULL)
            return false;

        // Create texture
        D3D11_TEXTURE2D_DESC desc;
        ZeroMemory(&desc, sizeof(desc));
        desc.Width = image_width;
        desc.Height = image_height;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0;

        ID3D11Texture2D* pTexture = NULL;
        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = image_data;
        subResource.SysMemPitch = desc.Width * 4;
        subResource.SysMemSlicePitch = 0;
        pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

        // Create texture view
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;
        pDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
        pTexture->Release();

        *out_width = image_width;
        *out_height = image_height;
        stbi_image_free(image_data);

        return true;
    }

    bool TabButton(std::string name, bool& bOpened, ImVec2 size = ImVec2(125, 30), ImColor textColor = ImColor(255, 255, 255)) {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(name.c_str());
        const ImVec2 cursorPos = ImGui::GetCurrentWindow()->DC.CursorPos;

        const ImRect total_bb(cursorPos, ImVec2(size.x + cursorPos.x, size.y + cursorPos.y));
        ImGui::ItemSize(size, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id))
            return false;


        bool hovered = ImGui::IsMouseHoveringRect(total_bb.Min, total_bb.Max);
        if (hovered) {
            textColor = ImColor(255, 0, 92);
            //ImGui::GetWindowDrawList()->AddLine(ImVec2(total_bb.Min.x, total_bb.Min.y + size.y), total_bb.Max, ImColor(255, 0, 92), 5);
        }

        if (bOpened) {
            textColor = ImColor(255, 0, 92);
        }

        bool is_hovered, held;
        bool pressed = ImGui::ButtonBehavior(total_bb, id, &is_hovered, &held, ImGuiButtonFlags_Repeat);
        if (pressed) {
            textColor = ImColor(255, 0, 92);

            bOpened = !bOpened;
        }

        // g.Style.ItemSpacing.x = 0.f;

        ImGui::GetWindowDrawList()->PushClipRect(total_bb.Min, total_bb.Max);
        ImGui::GetWindowDrawList()->AddRectFilled(total_bb.Min, total_bb.Max, ImColor(51, 51, 51));
        ImGui::GetWindowDrawList()->PopClipRect();
        ImGui::GetWindowDrawList()->AddText(ImVec2((cursorPos.x + (size.x / 2)) - (ImGui::CalcTextSize(name.c_str()).x / 2),
            (cursorPos.y + (size.y / 2)) - (ImGui::CalcTextSize(name.c_str()).y / 2)), textColor, name.c_str());
        //ImGui::PopStyleVar();

        if (hovered) {
            ImGui::GetWindowDrawList()->AddLine(ImVec2(total_bb.Min.x, total_bb.Min.y + size.y), total_bb.Max, ImColor(255, 0, 92), 2.5f);
        }

        if (bOpened) {
            ImGui::GetWindowDrawList()->AddLine(ImVec2(total_bb.Min.x, total_bb.Min.y + size.y), total_bb.Max, ImColor(255, 0, 92), 2.5f);
        }

        return pressed;
    }

    bool MainBar(const char* str_id, ImVec2 size) {
        const ImGuiStyle& style = ImGui::GetStyle();
        const ImGuiID id = ImGui::GetCurrentWindow()->GetID(str_id);
        ImVec2 cursorPos = ImGui::GetCurrentWindow()->DC.CursorPos;

        ImRect total_bb(cursorPos, ImVec2(size.x + cursorPos.x, size.y + cursorPos.y));
        ImGui::ItemSize(total_bb, style.FramePadding.y);
        if (!ImGui::ItemAdd(total_bb, id))
            return false;

        ImGui::GetWindowDrawList()->PushClipRect(total_bb.Min, total_bb.Max);
        ImGui::GetWindowDrawList()->AddRectFilled(total_bb.Min, total_bb.Max, ImColor(51, 51, 51));
    }

    void UIInit() {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;


        ImFontConfig font_config;
        font_config.OversampleH = 1; //or 2 is the same
        font_config.OversampleV = 1;
        font_config.PixelSnapH = 1;

        static const ImWchar ranges[] =
        {
            0x0020, 0x00FF, // Basic Latin + Latin Supplement
            0x0400, 0x044F, // Cyrillic
            0,
        };

        io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 16.f, &font_config, ranges);
        ImFontConfig config;
        config.MergeMode = true;
        config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
        static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

        io.Fonts->AddFontFromMemoryTTF(FA6PRO, sizeof(FA6PRO), 13.0f, &config, icon_ranges);

        this->pMenuFont = io.Fonts->AddFontFromMemoryTTF(MontserratRegular, sizeof(MontserratRegular), 15.f, &font_config, ranges);

        CExtractor::ExtractFile("sakura.png", logo, sizeof(logo));
        LoadTextureFromFile(STRING_T(CExtractor::GetTemporaryPath() + "sakura.png"), &pLogoTexture, &LogoWidth, &LogoHeight);

        io.IniFilename = nullptr;
        io.LogFilename = nullptr;

        io.WantSaveIniSettings = false;

        ImGuiStyle* style = &ImGui::GetStyle();
        //style->ItemSpacing.x = 5.f;
        style->Colors[ImGuiCol_::ImGuiCol_CheckMark] = ImVec4(1.0f, 0.f, 92.f / 255.0f, 1.00f);
        style->Colors[ImGuiCol_::ImGuiCol_SliderGrab] = ImVec4(255.f / 255.f, 0.f, 92.f / 255.0f, 1.00f);
        style->Colors[ImGuiCol_::ImGuiCol_Button] = ImVec4(255.f / 255.f, 0.f, 92.f / 255.0f, 1.00f);
        style->Colors[ImGuiCol_::ImGuiCol_ButtonActive] = ImVec4(35.f / 255.f, 0.f, 35.f / 255.0f, 1.00f);
        style->Colors[ImGuiCol_::ImGuiCol_ButtonHovered] = ImVec4(255.f / 255.f, 0.f, 92.f / 255.0f, 0.50f);
        style->Colors[ImGuiCol_::ImGuiCol_PopupBg] = ImVec4(33.f / 255.f, 33.f / 255.f, 33.f / 255.0f, 0.99f);
        style->Colors[ImGuiCol_::ImGuiCol_Header] = ImVec4(255.f / 255.f, 0.f, 92.f / 255.0f, 0.45f);
        style->Colors[ImGuiCol_::ImGuiCol_HeaderHovered] = ImVec4(255.f / 255.f, 0.f, 92.f / 255.0f, 0.85f);
        style->Colors[ImGuiCol_::ImGuiCol_HeaderActive] = ImVec4(255.f / 255.f, 0.f, 92.f / 255.0f, 0.35f);
        style->Colors[ImGuiCol_::ImGuiCol_FrameBgHovered] = ImVec4(255.f / 255.f, 0.f, 92.f / 255.0f, 0.75f);
        style->Colors[ImGuiCol_::ImGuiCol_FrameBg] = ImVec4(255.f / 255.f, 0.f, 92.f / 255.0f, 1.00f);

        ImGui_ImplWin32_Init(hWnd);
        ImGui_ImplDX11_Init(pDevice, pContext);
    }

	void UI() {
        static bool bVisualMenu = false, bAimMenu = false, bPlayerMenu = false, bWeaponMenu = false, bMiscMenu = false;
        static bool bNonStop;
        static int nHits, nCurrentTarget, nCurrentPoint;
        static float fRadiusFOV;
        static const char* pTargets[] = { "Argus 1", "Argus2" };
        static const char* pPoints[] = { "Argus 1", "Argus2" };

        ImGui::SetNextWindowSize(ImVec2(640, 405));
        DWORD flags = ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize;
        if (ImGui::Begin("Sakura", 0, flags)) {

            ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ItemSpacing, ImVec2(0.f, ImGui::GetStyle().ItemSpacing.y));
            if (TabButton(std::string(ICON_FA_EYE) + std::string(u8" Рендеринг"), bVisualMenu)) bAimMenu = false, bPlayerMenu = false, bWeaponMenu = false, bMiscMenu = false; ImGui::SameLine();
            if (TabButton(std::string(ICON_FA_SWORDS) + std::string(u8" Аим"), bAimMenu)) bVisualMenu = false, bPlayerMenu = false, bWeaponMenu = false, bMiscMenu = false; ImGui::SameLine();
            if (TabButton(std::string(ICON_FA_PERSON_RUNNING) + std::string(u8" Игрок"), bPlayerMenu)) bVisualMenu = false, bAimMenu = false, bWeaponMenu = false, bMiscMenu = false; ImGui::SameLine();
            if (TabButton(std::string(ICON_FA_KNIFE_KITCHEN) + std::string(u8" Оружие"), bWeaponMenu))bVisualMenu = false, bPlayerMenu = false, bAimMenu = false, bMiscMenu = false; ImGui::SameLine();
            if (TabButton(std::string(ICON_FA_LIST) + std::string(u8" Разное"), bMiscMenu))bVisualMenu = false, bPlayerMenu = false, bWeaponMenu = false, bAimMenu = false;
            ImGui::PopStyleVar();

            ImGui::Spacing();

            ImGui::PushFont(pMenuFont);
            if (bVisualMenu) {
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(51.f / 255.f, 51.f / 255.f, 51.f / 255.f, 1.f));
                if (ImGui::BeginChild("##LeftSide", ImVec2(309, 350))) {
                    auto pos = ImGui::GetCurrentWindow()->Pos;
                    ImGui::SetNextWindowPos({ pos.x + 10,pos.y + 10 });
                    if (ImGui::BeginChild("##Rebenok", { 289, 330 })) {
                        ImGui::Spacing();
                        ImGui::Text(u8"Раздел рендера");
                        ImGui::Spacing();
                        ImGui::Checkbox(u8"Силуэты врагов", &Settings::bSilhouettePlayer);
                        ImGui::Checkbox(u8"Силуэты объектов", &Settings::bSilhouetteObject);
                        ImGui::Checkbox(u8"Силуэты предметов", &Settings::bSilhouetteWeapon);
                        ImGui::Checkbox(u8"Клейморы", &Settings::bClaymoreDetectRadius);
                        ImGui::Checkbox(u8"Отключить ослепку", &Settings::bFlashbangDisable);
                        ImGui::EndChild();
                    }

                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(51.f / 255.f, 51.f / 255.f, 51.f / 255.f, 1.f));
                if (ImGui::BeginChild("##RightSide", ImVec2(308, 350), false)) {


                    ImGui::SetCursorPos(ImVec2(310 / 2 - 180 / 2, 350 / 2 - 135 / 2));
                    ImGui::Image((void*)pLogoTexture, ImVec2(180, 135));

                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
            }

            if (bAimMenu) {
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(51.f / 255.f, 51.f / 255.f, 51.f / 255.f, 1.f));
                if (ImGui::BeginChild("##LeftSide", ImVec2(309, 350))) {
                    auto pos = ImGui::GetCurrentWindow()->Pos;
                    ImGui::SetNextWindowPos({ pos.x + 10,pos.y + 10 });
                    if (ImGui::BeginChild("##Rebenok", { 289, 330 })) {
                        ImGui::Spacing();
                        ImGui::Text(u8"Раздел аима");
                        ImGui::Spacing();
                        ImGui::Checkbox(u8"Сайлент аим", &Settings::bSilentAim);
                        ImGui::Checkbox(u8"FOV аим", &Settings::bFovAim);
                        ImGui::Checkbox(u8"Включить хиты", &Settings::bFireHit);
                        ImGui::Checkbox(u8"Включить хиты с ножа", &Settings::bKnifeHit);

                        ImGui::EndChild();
                    }

                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(51.f / 255.f, 51.f / 255.f, 51.f / 255.f, 1.f));
                if (ImGui::BeginChild("##RightSide", ImVec2(308, 350), false)) {
                    auto pos = ImGui::GetCurrentWindow()->Pos;
                    ImGui::SetNextWindowPos({ pos.x + 10,pos.y + 10 });
                    if (ImGui::BeginChild("##Rebenok", { 289, 330 })) {
                        ImGui::Spacing();
                        ImGui::Text(u8"Настройки аима");

                        ImGui::Checkbox(u8"Прострел", &Settings::bWallshot);
                        ImGui::SliderFloat(u8"Радиус FOV", &Settings::nFovRadius, 5.f, 480.f, "%.1f");
                        ImGui::SliderInt(u8"Количество хитов:", &Settings::hitCount, 1, 15);
                        ImGui::SliderInt(u8"Задержка хитов:", &Settings::hitWait, 5, 400);
                        ImGui::Button(u8"Приклад");

                        ImGui::Combo(u8"Выбрать цель", &nCurrentTarget, pTargets, IM_ARRAYSIZE(pTargets));

                        ImGui::EndChild();
                    }


                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
            }

            if (bPlayerMenu) {
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(51.f / 255.f, 51.f / 255.f, 51.f / 255.f, 1.f));
                if (ImGui::BeginChild("##LeftSide", ImVec2(309, 350))) {
                    auto pos = ImGui::GetCurrentWindow()->Pos;
                    ImGui::SetNextWindowPos({ pos.x + 10,pos.y + 10 });
                    if (ImGui::BeginChild("##Rebenok", { 289, 330 })) {
                        ImGui::Spacing();
                        ImGui::Text(u8"Раздел игрока");
                        ImGui::Spacing();
                        ImGui::Checkbox(u8"Полет", &Settings::bFlyMode);
                        ImGui::Checkbox(u8"Невидимка", &Settings::bInvinsible);
                        ImGui::Checkbox(u8"Десинхрон", &Settings::bDesynchronization);
                        ImGui::Checkbox(u8"Телепорт", &Settings::bTeleportMode);
                        ImGui::Checkbox(u8"Краш всех игроков", &Settings::bCrashPlayers);
                        ImGui::Checkbox(u8"Быстрый подсад", &Settings::bFastClimb);
                        ImGui::Checkbox(u8"Подсад в одного", &Settings::bClimbExtra);
                        ImGui::Checkbox(u8"Спам Х", &Settings::bSpamX);

                        ImGui::EndChild();
                    }
                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(51.f / 255.f, 51.f / 255.f, 51.f / 255.f, 1.f));
                if (ImGui::BeginChild("##RightSide", ImVec2(308, 350), false)) {
                    auto pos = ImGui::GetCurrentWindow()->Pos;
                    ImGui::SetNextWindowPos({ pos.x + 10,pos.y + 10 });
                    if (ImGui::BeginChild("##Rebenok", { 289, 330 })) {
                        ImGui::Spacing();
                        ImGui::Text(u8"Настройки полета");
                        ImGui::SliderFloat(u8"Дистанция", &fRadiusFOV, 5.f, 480.f, "%.1f");
                        ImGui::Text(u8"Настройки невидимости");
                        ImGui::Button(u8"RAGE");
                        ImGui::Text(u8"Телепорт");
                        ImGui::Button(u8"Сохранить текущию позицию");
                        ImGui::Button(u8"Телепортироваться сохр. точке");
                        ImGui::Combo(u8"Выбрать точку", &nCurrentPoint, pPoints, IM_ARRAYSIZE(pPoints));
                        ImGui::EndChild();
                    }
                    //ImGui::Combo("Выбрать цель", &nCurrentTarget, &pTargets);

                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
            }

            if (bWeaponMenu) {
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(51.f / 255.f, 51.f / 255.f, 51.f / 255.f, 1.f));
                if (ImGui::BeginChild("##LeftSide", ImVec2(309, 350))) {
                    auto pos = ImGui::GetCurrentWindow()->Pos;
                    ImGui::SetNextWindowPos({ pos.x + 10,pos.y + 10 });
                    if (ImGui::BeginChild("##Rebenok", { 289, 330 })) {
                        ImGui::Spacing();
                        ImGui::Text(u8"Раздел оружии");
                        ImGui::Spacing();
                        ImGui::Checkbox(u8"Отключить отдачу", &Settings::bNoRecoil);
                        ImGui::Checkbox(u8"Отключить разброс", &Settings::bNoSpread);
                        ImGui::Checkbox(u8"Отключить увод", &Settings::bNoSway);
                        ImGui::Checkbox(u8"Быстрая перезарядка", &Settings::bFastReload);
                        ImGui::Checkbox(u8"Быстрый нож", &Settings::bFastKnife);
                        ImGui::Checkbox(u8"Быстрый зум", &Settings::bFastZoom);
                        ImGui::Checkbox(u8"Рапид", &Settings::bRapidFire);

                        ImGui::EndChild();
                    }
                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(51.f / 255.f, 51.f / 255.f, 51.f / 255.f, 1.f));
                if (ImGui::BeginChild("##RightSide", ImVec2(308, 350), false)) {
                    auto pos = ImGui::GetCurrentWindow()->Pos;
                    ImGui::SetNextWindowPos({ pos.x + 10,pos.y + 10 });
                    if (ImGui::BeginChild("##Rebenok", { 289, 330 })) {
                        ImGui::Spacing();
                        ImGui::Text(u8"Настройки рапида");
                        ImGui::SliderFloat(u8"Скорость", &fRadiusFOV, 5.f, 480.f, "%.1f");

                        ImGui::EndChild();
                    }
                    //ImGui::Combo("Выбрать цель", &nCurrentTarget, &pTargets);

                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
            }

            if (bMiscMenu) {
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(51.f / 255.f, 51.f / 255.f, 51.f / 255.f, 1.f));
                if (ImGui::BeginChild("##LeftSide", ImVec2(309, 350))) {
                    auto pos = ImGui::GetCurrentWindow()->Pos;
                    ImGui::SetNextWindowPos({ pos.x + 10,pos.y + 10 });
                    if (ImGui::BeginChild("##Rebenok", { 289, 330 })) {
                        ImGui::Spacing();
                        ImGui::Text(u8"Раздел функции");
                        ImGui::Spacing();
                        ImGui::Checkbox(u8"Отключить кик за АФК", &Settings::bDisableKickByAFK);
                        ImGui::Checkbox(u8"Включить голосование", &Settings::bVotingEnable);
                        ImGui::Checkbox(u8"Пользователские статистики", &Settings::bCustomStatistics);
                        ImGui::Checkbox(u8"Кикнуть себя", &Settings::bKickSelf);
                        ImGui::Checkbox(u8"Убить себя", &Settings::bSuicide);
                        ImGui::Checkbox(u8"Коммуникация", &Settings::bCommunication);
                        ImGui::Checkbox(u8"Проверять спавн", &Settings::bSpawnAnalyse);

                        ImGui::EndChild();
                    }
                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(51.f / 255.f, 51.f / 255.f, 51.f / 255.f, 1.f));
                if (ImGui::BeginChild("##RightSide", ImVec2(308, 350), false)) {
                    auto pos = ImGui::GetCurrentWindow()->Pos;
                    ImGui::SetNextWindowPos({ pos.x + 10,pos.y + 10 });
                    if (ImGui::BeginChild("##Rebenok", { 289, 330 })) {
                        ImGui::Spacing();
                        ImGui::Text(u8"Настройки рапида");
                        ImGui::SliderFloat(u8"Скорость", &fRadiusFOV, 5.f, 480.f, "%.1f");
                        //ImGui::Combo("Выбрать цель", &nCurrentTarget, &pTargets);

                        ImGui::EndChild();
                    }

                    ImGui::EndChild();
                }
                ImGui::PopStyleColor();
            }

            ImGui::PopFont();

            if (!bMiscMenu && !bWeaponMenu && !bPlayerMenu && !bAimMenu && !bVisualMenu) {
                auto pSize = ImGui::GetCurrentWindow()->Size;
                float x = pSize.x / 2 - LogoWidth / 2;
                float y = pSize.y / 2 - LogoHeight / 2;
                ImGui::SetCursorPos({ (float)x, (float)y });
                ImGui::Image((void*)pLogoTexture, { (float)LogoWidth, (float)LogoHeight });
            }
        }

        ImGui::End();
	}

public:
	ImFont* pMenuFont;
	ImFont* pAdvanceFont;

	EMenuCategory pCategory = EMenuCategory::EMC_Main;
	HWND hWnd = NULL;
	WNDPROC oWndProc;
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* pRenderTargetView;
    int LogoWidth = 0;
    int LogoHeight = 0;
    ID3D11ShaderResourceView* pLogoTexture = NULL;
};
